#include <string.h>

#include "hawser/hawser.h"

#include "hawser_internal.h"
#include "id.h"


/**
 * Checks whether ID characters are valid (default implementation).
 */
static BOOL
is_valid_id_char(char current, char previous)
{
	UNUSED(previous);

	if (FALSE
		|| (current >= 'A' && current <= 'Z')
		|| (current >= 'a' && current <= 'z')
		|| (current >= '0' && current <= '9')
		|| (current == '_')
		|| (current == '-')
		|| (current == '\0')
	) {
		return TRUE;
	}

	return FALSE;
}


HAWSERresult
id_checked_copy(
    char *id,
    const char *string,
    size_t min_strlen,
    size_t max_strlen,
    ID_VALIDATOR validator_fn
)
{
	char *pNull;
	size_t cbString;
	size_t ibString;
	char previous = '\0';

	/* Maximum length */
	pNull = memchr(string, '\0', max_strlen + 1);
	if (!pNull) {
		return HAWSER_INVALID;
	}

	/* Minimum length */
	cbString = pNull - string;
	if (cbString < min_strlen) {
		return HAWSER_INVALID;
	}

	/* Valid characters */
	if (validator_fn == NULL) {
		validator_fn = &is_valid_id_char;
	}
	for (ibString = 0; ibString <= cbString; ibString++) {
		if ((*validator_fn)(string[ibString], previous) == FALSE) {
			return HAWSER_INVALID;
		}
		previous = string[ibString];
	}

	/* Do the copy */
	memcpy(id, string, cbString + 1);

	return HAWSER_OK;
}
