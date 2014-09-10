#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "hawser/hawser.h"
#include "hawser/ec2.h"

#include "../hawser_internal.h"


/**
 * Boolean value for use in logical expressions.
 */
#define BOOL int


/**
 * True value for use in logical expressions.
 */
#define TRUE 1


/**
 * False value for use in logical expressions.
 */
#define FALSE 0


/**
 * Common return value when strings are equal.
 */
#define COMPARE_EQUAL 0


/**
 * Minimum length (in bytes) of an EC2 resource ID string.
 */
#define ID_MIN_LENGTH 11 /* "i-12345678\0" */


/**
 * Maximum length (in bytes) of an EC2 resource ID string.
 *
 * Based on HAWSER_EC2_RESOURCE_ID_STRING_LENGTH which is defined publicly in
 * <hawser/ec2.h>.
 */
#define ID_MAX_LENGTH HAWSER_EC2_RESOURCE_ID_STRING_LENGTH


/**
 * Length (in bytes) of the ID part of an EC2 resource ID string.
 */
#define ID_ID_LENGTH 8


/**
 * An EC2 resource ID.
 */
struct HAWSER_EC2_RESOURCE_ID {
	HAWSER_EC2_RESOURCE_TYPE resourceType; /* Type of the resource. */
	char id[ID_ID_LENGTH + 1];             /* Unique ID + '\0'.     */
};


/**
 * Type to hold various data about a resource type.
 */
typedef struct {
	HAWSER_EC2_RESOURCE_TYPE resourceType;
	const char *resourceTypeName;
	const char *tag;
} RESOURCE_TYPE_ROW;


/**
 * Collection of data about each resource type.
 */
static const RESOURCE_TYPE_ROW RESOURCE_TYPES[] = {
	{ HAWSER_EC2_CUSTOMER_GATEWAY,       "customer-gateway",       "cgw"    },
	{ HAWSER_EC2_DHCP_OPTIONS,           "dhcp-options",           "dopt"   },
	{ HAWSER_EC2_IMAGE,                  "image",                  "ami"    },
	{ HAWSER_EC2_INSTANCE,               "instance",               "i"      },
	{ HAWSER_EC2_INTERNET_GATEWAY,       "internet-gateway",       "igw"    },
	{ HAWSER_EC2_NETWORK_ACL,            "network-acl",            "acl"    },
	{ HAWSER_EC2_NETWORK_INTERFACE,      "network-interface",      "eni"    },
	{ HAWSER_EC2_ROUTE_TABLE,            "route-table",            "rtb"    },
	{ HAWSER_EC2_SECURITY_GROUP,         "security-group",         "sg"     },
	{ HAWSER_EC2_SNAPSHOT,               "snapshot",               "snap"   },
	{ HAWSER_EC2_SPOT_INSTANCES_REQUEST, "spot-instances-request", "sir"    },
	{ HAWSER_EC2_SUBNET,                 "subnet",                 "subnet" },
	{ HAWSER_EC2_VOLUME,                 "volume",                 "vol"    },
	{ HAWSER_EC2_VPC,                    "vpc",                    "vpc"    },
	{ HAWSER_EC2_VPN_CONNECTION,         "vpn-connection",         "vpn"    },
	{ HAWSER_EC2_VPN_GATEWAY,            "vpn-gateway",            "vgw"    },
	{ 0,                                 NULL,                     NULL     }
};


/**
 * Minimum length (in bytes) of the tag part of a resource ID string.
 */
#define TAG_MIN_LENGTH (ID_MIN_LENGTH - ID_ID_LENGTH - 2)


/**
 * Maximum length (in bytes) of the tag part of a resource ID string.
 */
#define TAG_MAX_LENGTH (ID_MAX_LENGTH - ID_ID_LENGTH - 2)


/**
 * Checks whether a HAWSER_EC2_RESOURCE_ID struct looks OK.
 */
static BOOL
ec2_id_is_valid(const HAWSER_EC2_RESOURCE_ID *id)
{
	if (FALSE
		|| id == NULL
		|| id->resourceType < HAWSER_EC2_RESOURCE_TYPE_MIN
		|| id->resourceType > HAWSER_EC2_RESOURCE_TYPE_MAX
		|| id->id[8] != '\0'
	) {
		return FALSE;
	}

	return TRUE;
}


HAWSERresult
hawser_ec2_id_read(HAWSER_EC2_RESOURCE_ID *id, const char *string)
{
	char *pNull;
	size_t cbString;
	char *pHyphen;
	size_t cbTag;
	const RESOURCE_TYPE_ROW *type = RESOURCE_TYPES;
	BOOL found = FALSE;

	REQUIRE_NOT_NULL(id);
	REQUIRE_NOT_NULL(string);

	/* Check the length looks good. */
	pNull = memchr(string, '\0', ID_MAX_LENGTH);
	if (!pNull) {
		return HAWSER_INVALID;
	}

	cbString = pNull - string;
	if (cbString < ID_MIN_LENGTH) {
		return HAWSER_INVALID;
	}

	/* Find the tag part. */
	pHyphen = memchr(string, '-', cbString);
	if (!pHyphen) {
		return HAWSER_INVALID;
	}

	cbTag = pHyphen - string;
	if (cbTag < TAG_MIN_LENGTH || cbTag > TAG_MAX_LENGTH) {
		return HAWSER_INVALID;
	}

	if (cbString - cbTag - 1 /* '-' */ != ID_ID_LENGTH) {
		return HAWSER_INVALID;
	}

	/* Loop over possible types. */
	while (type->resourceTypeName) {
		if (strncmp(string, type->tag, cbTag) == COMPARE_EQUAL) {
			id->resourceType = type->resourceType;
			strcpy(id->id, pHyphen + 1);
			id->id[8] = '\0';
			found = TRUE;
			break;
		}

		type++;
	}

	if (found == FALSE) {
		return HAWSER_INVALID;
	}

	assert(ec2_id_is_valid(id) == TRUE);
	return HAWSER_OK;
}


const char *
hawser_ec2_id_write(char *string, const HAWSER_EC2_RESOURCE_ID *id)
{
	static char internalOutput[ID_MAX_LENGTH];
	char *output = string ? string : internalOutput;

	if (ec2_id_is_valid(id) == FALSE) {
		return NULL;
	}

	output[0] = '\0';
	strcat(output, RESOURCE_TYPES[id->resourceType].tag);
	strcat(output, "-");
	strcat(output, id->id);

	return output;
}
