#ifndef __ENCODINGS_H
#define __ENCODINGS_H

#include <stddef.h>

#include "hawser/hawser.h"

#include "buffer.h"


/**
 * Base-16 encodes an input string.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * Returns HAWSER_INVALID if the supplied buffer is invalid. (TODO)
 * Returns HAWSER_MEMORY if a memory allocation fails. (TODO)
 */
HAWSERresult
encode_base16(BUFFER *bufDestination, const char *szInput, size_t cbInput);


/**
 * URI-encodes an input string.
 *
 * Returns HAWSER_NULL if either of the supplied pointers are NULL.
 * Returns HAWSER_INVALID if the supplied buffer is invalid. (TODO)
 * Returns HAWSER_MEMORY if a memory allocation fails. (TODO)
 */
HAWSERresult
encode_uri(BUFFER *bufDestination, const char *szInput, size_t cbInput);


#endif /* __ENCODINGS_H */
