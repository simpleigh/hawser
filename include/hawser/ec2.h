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
	HAWSER_EC2_CUSTOMER_GATEWAY = 0,
	HAWSER_EC2_DHCP_OPTIONS,
	HAWSER_EC2_IMAGE,
	HAWSER_EC2_INSTANCE,
	HAWSER_EC2_INTERNET_GATEWAY,
	HAWSER_EC2_NETWORK_ACL,
	HAWSER_EC2_NETWORK_INTERFACE,
	HAWSER_EC2_ROUTE_TABLE,
	HAWSER_EC2_SECURITY_GROUP,
	HAWSER_EC2_SNAPSHOT,
	HAWSER_EC2_SPOT_INSTANCES_REQUEST,
	HAWSER_EC2_SUBNET,
	HAWSER_EC2_VOLUME,
	HAWSER_EC2_VPC,
	HAWSER_EC2_VPN_CONNECTION,
	HAWSER_EC2_VPN_GATEWAY
} HAWSER_EC2_RESOURCE_TYPE;


/**
 * Minimum valid EC2 resource type.
 */
#define HAWSER_EC2_RESOURCE_TYPE_MIN HAWSER_EC2_CUSTOMER_GATEWAY


/**
 * Maximum valid EC2 resource type.
 */
#define HAWSER_EC2_RESOURCE_TYPE_MAX HAWSER_EC2_VPN_GATEWAY


/**
 * Number of bytes required to store an EC2 resource ID string.
 *
 * Calculated as "subnet-12345678" plus terminating NULL byte.
 */
#define HAWSER_EC2_RESOURCE_ID_STRING_LENGTH 16


/**
 * Number of bytes required to store the ID part of an EC2 resource ID string.
 *
 * DOES NOT INCLUDE terminating NULL byte.
 */
#define HAWSER_EC2_RESOURCE_ID_ID_LENGTH 8


/**
 * An EC2 resource ID.
 */
typedef struct {
	HAWSER_EC2_RESOURCE_TYPE resourceType;         /* Type of the resource. */
	char id[HAWSER_EC2_RESOURCE_ID_ID_LENGTH + 1]; /* Unique ID.            */
} HAWSER_EC2_RESOURCE_ID;


/**
 * Parses a string into a HAWSER_EC2_RESOURCE_ID struct.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * STRING must be NULL-terminated.
 * This function will examine up to HAWSER_EC2_RESOURCE_ID_STRING_LENGTH bytes
 * of STRING while looking for the terminating NULL.
 */
HAWSERresult hawser_ec2_id_read(HAWSER_EC2_RESOURCE_ID *id, const char *string);


/**
 * Writes a HAWSER_EC2_RESOURCE_ID struct as a string.
 *
 * It places the result in STRING, which should be at least
 * HAWSER_EC2_RESOURCE_ID_STRING_LENGTH bytes in length.
 * If STRING is NULL then the result is placed in a static array.
 *
 * Returns a pointer to the ID string, or NULL on error.
 */
const char *hawser_ec2_id_write(char *string, const HAWSER_EC2_RESOURCE_ID *id);


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_EC2_H */
