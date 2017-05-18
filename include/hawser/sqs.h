#ifndef __HAWSER_SQS_H
#define __HAWSER_SQS_H

#include "hawser.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Bytes required to store a string representation of an SQS resource ID.
 */
#define SQS_ID_BYTES 81


/**
 * SQS resource ID.
 */
typedef struct {
	char queue_name[SQS_ID_BYTES];
} SQS_ID;


/**
 * Parses a string into an SQS_ID struct.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * Returns HAWSER_INVALID if STRING cannot be parsed.
 *
 * STRING must be NUL-terminated, and this function will examine up to
 * SQS_ID_BYTES bytes of STRING while looking for the terminating NUL.
 */
HAWSERresult sqs_id_from_string(SQS_ID *id, const char *string);


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_SNS_H */
