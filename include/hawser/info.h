#ifndef __HAWSER_INFO_H
#define __HAWSER_INFO_H

#include "hawser.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Obtains the name for a region.
 *
 * Places a pointer to the region string in DEST.
 *
 * Returns HAWSER_INVALID if the REGION is out of range.
 * Returns HAWSER_NULL if DEST is NULL.
 */
HAWSERresult aws_region(
	AWS_REGION region,
	const char **dest
);


/**
 * Obtains the namespace for a service.
 *
 * Places a pointer to the namespace string in DEST.
 *
 * Returns HAWSER_INVALID if the SERVICE is out of range.
 * Returns HAWSER_NULL if DEST is NULL.
 */
HAWSERresult aws_service_namespace(
	AWS_SERVICE service,
	const char **dest
);


/**
 * Obtains the web endpoint for a service and region.
 *
 * Places a pointer to the endpoint string in DEST.
 *
 * Returns HAWSER_INVALID if the SERVICE or REGION are out of range.
 * Returns HAWSER_NULL if DEST is NULL.
 * Returns HAWSER_BAD_REGION if SERVICE is not supported in REGION.
 */
HAWSERresult aws_endpoint(
	AWS_SERVICE service,
	AWS_REGION region,
	const char **dest
);


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_INFO_H */
