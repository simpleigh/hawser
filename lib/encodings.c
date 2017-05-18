#include <stdio.h>

#include "encodings.h"

#ifndef FALSE
#define FALSE 0
#endif

static const char
BASE16[] = "0123456789abcdef";

void
encode_base16(BUFFER *bufDestination, const char *szInput, size_t cbInput)
{
	size_t ibInput;
	unsigned char c;
	char encoded[2];

	for (ibInput = 0; ibInput < cbInput; ibInput++) {
		c = szInput[ibInput];
		encoded[0] = BASE16[c >> 4];
		encoded[1] = BASE16[c & 0xF];
		buffer_nappend(bufDestination, encoded, 2);
	}
}

void
encode_uri(BUFFER *bufDestination, const char *szInput, size_t cbInput)
{
	size_t ibInput;
	unsigned char c;
	char encoded[4]; /* '%' 'x' 'x' '\0' */

	for (ibInput = 0; ibInput < cbInput; ibInput++) {
		c = szInput[ibInput];
		if (FALSE
			|| (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9')
			|| (c == '-')
			|| (c == '_')
			|| (c == '.')
			|| (c == '~')
		) {
			/* Copy over one character */
			buffer_nappend(bufDestination, szInput + ibInput, 1);
		} else {
			/* Use sprintf to encode character as hex */
			sprintf(encoded, "%%%2x", c);
			buffer_nappend(bufDestination, encoded, 3);
		}
	}
}
