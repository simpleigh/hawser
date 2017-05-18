#ifndef __HAWSER_LAMBDA_H
#define __HAWSER_LAMBDA_H

#include "hawser.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Bytes required to store a string representation of an Lambda resource ID.
 */
#define LAMBDA_ID_BYTES 257


/**
 * Lambda resource ID.
 */
typedef struct {
	char function_name[LAMBDA_ID_BYTES];
} LAMBDA_ID;


/**
 * Parses a string into an LAMBDA_ID struct.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * Returns HAWSER_INVALID if STRING cannot be parsed.
 *
 * STRING must be NUL-terminated, and this function will examine up to
 * LAMBDA_ID_BYTES bytes of STRING while looking for the terminating NUL.
 */
HAWSERresult lambda_id_from_string(LAMBDA_ID *id, const char *string);


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_LAMBDA_H */
