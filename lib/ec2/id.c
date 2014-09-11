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
 *
 * DOES NOT INCLUDE terminating NULL byte.
 */
#define ID_MIN_STRLEN 10 /* "i-12345678" */


/**
 * Maximum length (in bytes) of an EC2 resource ID string.
 *
 * Based on EC2_ID_MAX_BYTES defined in <hawser/ec2.h>.
 * DOES NOT INCLUDE terminating NULL byte.
 */
#define ID_MAX_STRLEN (EC2_ID_MAX_BYTES - 1)


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
 *
 * DOES NOT INCLUDE terminating NULL byte.
 */
#define TAG_MIN_STRLEN (ID_MIN_STRLEN - EC2_ID_ID_BYTES - 1)


/**
 * Maximum length (in bytes) of the tag part of a resource ID string.
 *
 * DOES NOT INCLUDE terminating NULL byte.
 */
#define TAG_MAX_STRLEN (ID_MAX_STRLEN - EC2_ID_ID_BYTES - 1)


/**
 * Checks whether ID characters are valid hex digits.
 */
static BOOL
ec2_id_chars_valid(const char *id)
{
	size_t i;
	char c;

	for (i = 0; i < EC2_ID_ID_BYTES; i++) {
		c = id[i];
		if ((c < '0') || (c > '9' && c < 'a') || (c > 'f')) {
			return FALSE;
		}
	}

	return TRUE;
}


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
		|| ec2_id_chars_valid(id->id) == FALSE
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
	pNull = memchr(string, '\0', EC2_ID_MAX_BYTES);
	if (!pNull) {
		return HAWSER_INVALID;
	}

	cbString = pNull - string;
	if (cbString < ID_MIN_STRLEN) {
		return HAWSER_INVALID;
	}

	/* Find the tag part. */
	pHyphen = memchr(string, '-', cbString);
	if (!pHyphen) {
		return HAWSER_INVALID;
	}

	cbTag = pHyphen - string;
	if (cbTag < TAG_MIN_STRLEN || cbTag > TAG_MAX_STRLEN) {
		return HAWSER_INVALID;
	}

	if (cbString != cbTag + 1 + EC2_ID_ID_BYTES) { /* 1 byte for '-'. */
		return HAWSER_INVALID;
	}

	/* Check id characters are valid. */
	if (ec2_id_chars_valid(pHyphen + 1) == FALSE) {
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
	static char internalOutput[EC2_ID_MAX_BYTES];
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
