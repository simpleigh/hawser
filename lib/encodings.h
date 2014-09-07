#ifndef __ENCODINGS_H
#define __ENCODINGS_H

#include "buffer.h"

void encode_base16(BUFFER *bufDestination, const char *szInput, size_t cbInput);
void encode_uri(BUFFER *bufDestination, const char *szInput, size_t cbInput);

#endif /* __ENCODINGS_H */
