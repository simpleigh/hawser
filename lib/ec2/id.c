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
 * Based on EC2_ID_STRLEN defined in <hawser/ec2.h>.
 */
#define ID_MAX_LENGTH EC2_ID_STRLEN


/**
 * Type to hold various data about a resource type.
 */
typedef struct {
	EC2_RT type;
	const char *name;
	const char *tag;
} RT_ROW;


/**
 * Collection of data about each resource type.
 */
static const RT_ROW RESOURCE_TYPES[] = {
	{ EC2_CUSTOMER_GATEWAY,       "customer-gateway",       "cgw"    },
	{ EC2_DHCP_OPTIONS,           "dhcp-options",           "dopt"   },
	{ EC2_IMAGE,                  "image",                  "ami"    },
	{ EC2_INSTANCE,               "instance",               "i"      },
	{ EC2_INTERNET_GATEWAY,       "internet-gateway",       "igw"    },
	{ EC2_NETWORK_ACL,            "network-acl",            "acl"    },
	{ EC2_NETWORK_INTERFACE,      "network-interface",      "eni"    },
	{ EC2_ROUTE_TABLE,            "route-table",            "rtb"    },
	{ EC2_SECURITY_GROUP,         "security-group",         "sg"     },
	{ EC2_SNAPSHOT,               "snapshot",               "snap"   },
	{ EC2_SPOT_INSTANCES_REQUEST, "spot-instances-request", "sir"    },
	{ EC2_SUBNET,                 "subnet",                 "subnet" },
	{ EC2_VOLUME,                 "volume",                 "vol"    },
	{ EC2_VPC,                    "vpc",                    "vpc"    },
	{ EC2_VPN_CONNECTION,         "vpn-connection",         "vpn"    },
	{ EC2_VPN_GATEWAY,            "vpn-gateway",            "vgw"    },
	{ 0,                          NULL,                     NULL     }
};


/**
 * Minimum length (in bytes) of the tag part of a resource ID string.
 */
#define TAG_MIN_LENGTH (ID_MIN_LENGTH - EC2_ID_IDLEN - 2)


/**
 * Maximum length (in bytes) of the tag part of a resource ID string.
 */
#define TAG_MAX_LENGTH (ID_MAX_LENGTH - EC2_ID_IDLEN - 2)


/**
 * Checks whether a HAWSER_EC2_RESOURCE_ID struct looks OK.
 */
static BOOL
ec2_id_valid(const EC2_ID *id)
{
	if (FALSE
		|| id == NULL
		|| id->resourceType < EC2_RTMIN
		|| id->resourceType > EC2_RTMAX
		|| id->id[8] != '\0'
	) {
		return FALSE;
	}

	return TRUE;
}


HAWSERresult
ec2_ptoid(EC2_ID *id, const char *string)
{
	char *pNull;
	size_t cbString;
	char *pHyphen;
	size_t cbTag;
	const RT_ROW *row = RESOURCE_TYPES;
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

	if (cbString - cbTag - 1 /* '-' */ != EC2_ID_IDLEN) {
		return HAWSER_INVALID;
	}

	/* Loop over possible types. */
	while (row->name) {
		if (strncmp(string, row->tag, cbTag) == COMPARE_EQUAL) {
			id->resourceType = row->type;
			strcpy(id->id, pHyphen + 1);
			id->id[8] = '\0';
			found = TRUE;
			break;
		}

		row++;
	}

	if (found == FALSE) {
		return HAWSER_INVALID;
	}

	assert(ec2_id_valid(id) == TRUE);
	return HAWSER_OK;
}


const char *
ec2_idtop(char *string, const EC2_ID *id)
{
	static char internalOutput[ID_MAX_LENGTH];
	char *output = string ? string : internalOutput;

	if (ec2_id_valid(id) == FALSE) {
		return NULL;
	}

	output[0] = '\0';
	strcat(output, RESOURCE_TYPES[id->resourceType].tag);
	strcat(output, "-");
	strcat(output, id->id);

	return output;
}
