#ifndef __HAWSER_SNS_H
#define __HAWSER_SNS_H

#include "../hawser.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Bytes required to store a string representation of an SNS resource ID.
 */
#define SNS_ID_BYTES 257


/**
 * SNS resource ID.
 */
typedef struct {
	char topic_name[SNS_ID_BYTES];
} SNS_ID;


/**
 * Parses a string into an SNS_ID struct.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * Returns HAWSER_INVALID if STRING cannot be parsed.
 *
 * STRING must be NUL-terminated, and this function will examine up to
 * SNS_ID_BYTES bytes of STRING while looking for the terminating NUL.
 */
HAWSERresult sns_id_from_string(SNS_ID *id, const char *string);


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_SNS_H */
