#include <stdio.h>

#include "encodings.h"

#ifndef FALSE
#define FALSE 0
#endif

void
encode_uri(BUFFER *bufDestination, const char *szInput)
{
	unsigned char c;
	char encoded[4]; /* '%' 'x' 'x' '\0' */

	while ((c = *szInput) != '\0') {
		if (FALSE
			|| (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9')
			|| (c == '-')
			|| (c == '_')
			|| (c == '.')
			|| (c == '~')
		) {
			buffer_nappend(bufDestination, szInput, 1);
		} else {
			sprintf(encoded, "%%%2x", c);
			buffer_nappend(bufDestination, encoded, 3);
		}

		szInput++;
	}
}
