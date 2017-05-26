#include <stdio.h>

#include "hawser/hawser.h"

#include "hawser_internal.h"
#include "buffer.h"
#include "encodings.h"


/**
 * Base-16 source characters.
 */
static const char
BASE16[] = "0123456789abcdef";


HAWSERresult
encode_base16(BUFFER *bufDestination, const char *szInput, size_t cbInput)
{
	size_t ibInput;
	unsigned char c;
	char encoded[2];

	REQUIRE_NOT_NULL(bufDestination);
	REQUIRE_NOT_NULL(szInput);

	for (ibInput = 0; ibInput < cbInput; ibInput++) {
		c = szInput[ibInput];
		encoded[0] = BASE16[c >> 4];
		encoded[1] = BASE16[c & 0xF];
		/* TODO: check return value */
		buffer_nappend(bufDestination, encoded, 2);
	}

	return HAWSER_OK;
}


HAWSERresult
encode_uri(BUFFER *bufDestination, const char *szInput, size_t cbInput)
{
	size_t ibInput;
	unsigned char c;
	char encoded[4]; /* '%' 'x' 'x' '\0' */

	REQUIRE_NOT_NULL(bufDestination);
	REQUIRE_NOT_NULL(szInput);

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
			/* TODO: check return value */
			buffer_nappend(bufDestination, szInput + ibInput, 1);
		} else {
			/* Use sprintf to encode character as hex */
			sprintf(encoded, "%%%2x", c);
			/* TODO: check return value */
			buffer_nappend(bufDestination, encoded, 3);
		}
	}

	return HAWSER_OK;
}
