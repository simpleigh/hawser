#ifndef __HAWSER_EC2_H
#define __HAWSER_EC2_H

#include "hawser.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Types of EC2 resource.
 */
typedef enum {
	EC2_CUSTOMER_GATEWAY = 0,
	EC2_DHCP_OPTIONS,
	EC2_IMAGE,
	EC2_INSTANCE,
	EC2_INTERNET_GATEWAY,
	EC2_NETWORK_ACL,
	EC2_NETWORK_INTERFACE,
	EC2_ROUTE_TABLE,
	EC2_SECURITY_GROUP,
	EC2_SNAPSHOT,
	EC2_SPOT_INSTANCES_REQUEST,
	EC2_SUBNET,
	EC2_VOLUME,
	EC2_VPC,
	EC2_VPN_CONNECTION,
	EC2_VPN_GATEWAY
} EC2_RT;


/**
 * Minimum valid EC2 resource type.
 */
#define EC2_RTMIN EC2_CUSTOMER_GATEWAY


/**
 * Maximum valid EC2 resource type.
 */
#define EC2_RTMAX EC2_VPN_GATEWAY


/**
 * Number of bytes required to store an EC2 resource ID string.
 *
 * Calculated as "subnet-12345678" plus terminating NULL byte.
 */
#define EC2_ID_STRLEN 16


/**
 * Number of bytes required to store the ID part of an EC2 resource ID string.
 *
 * DOES NOT INCLUDE terminating NULL byte.
 */
#define EC2_ID_IDLEN 8


/**
 * An EC2 resource ID.
 */
typedef struct {
	EC2_RT resourceType;       /* Type of the resource. */
	char id[EC2_ID_IDLEN + 1]; /* Unique ID.            */
} EC2_ID;


/**
 * Parses a string into an EC2_ID struct.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * Returns HAWSER_INVALID if STRING cannot be parsed.
 *
 * STRING must be NULL-terminated, and this function will examine up to
 * EC2_ID_STRLEN bytes of STRING while looking for the terminating NULL.
 */
HAWSERresult ec2_ptoid(EC2_ID *id, const char *string);


/**
 * Writes an EC2_ID struct as a string.
 *
 * It places the result in STRING, which should be at least
 * EC2_ID_STRLEN bytes in length.
 * If STRING is NULL then the result is placed in a static array.
 *
 * Returns a pointer to the parsed output, or NULL on error.
 */
const char *ec2_idtop(char *string, const EC2_ID *id);


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_EC2_H */
