#ifndef __ENCODINGS_H
#define __ENCODINGS_H

#include "buffer.h"

void encode_base16(BUFFER *bufDestination, const char *szInput);
void encode_uri(BUFFER *bufDestination, const char *szInput);

#endif /* __ENCODINGS_H */
