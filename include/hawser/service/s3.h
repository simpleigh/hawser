#ifndef __HAWSER_S3_H
#define __HAWSER_S3_H

#include "../hawser.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Bytes required to store a string representation of an S3 resource ID.
 */
#define S3_ID_BYTES 64


/**
 * S3 resource ID.
 */
typedef struct {
	char bucket_name[S3_ID_BYTES];
} S3_ID;


/**
 * Parses a string into an S3_ID struct.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * Returns HAWSER_INVALID if STRING cannot be parsed.
 *
 * STRING must be NUL-terminated, and this function will examine up to
 * S3_ID_BYTES bytes of STRING while looking for the terminating NUL.
 */
HAWSERresult s3_id_from_string(S3_ID *id, const char *string);


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_S3_H */
