#include <string.h>

#include "hawser/hawser.h"
#include "hawser/service/sqs.h"

#include "../../hawser_internal.h"
#include "../id.h"


/**
 * Minimum characters in an SQS ID string.
 */
#define ID_MIN_STRLEN 1


/**
 * Maximum characters in an SQS ID string.
 */
#define ID_MAX_STRLEN 80


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
		|| (current == '.')
		|| (current == '\0')
	) {
		return TRUE;
	}

	return FALSE;
}


HAWSERresult
sqs_id_from_string (SQS_ID *id, const char *string)
{
	char *pNull, *pDot;

	REQUIRE_NOT_NULL(id);
	REQUIRE_NOT_NULL(string);

	/* Check that the only occurrence of a '.' is for a FIFO queue */
	pNull = memchr(string, '\0', ID_MAX_STRLEN + 1);
	if (!pNull) {
		return HAWSER_INVALID;
	}

	pDot = memchr(string, '.', pNull - string);
	if (pDot &&
		(pNull - pDot != 5 || strncmp(pDot, ".fifo", 5) != COMPARE_EQUAL)
	) {
		return HAWSER_INVALID;
	}

	return id_checked_copy(
		id->queue_name,
		string,
		ID_MIN_STRLEN,
		ID_MAX_STRLEN,
		&is_valid_id_char
	);
}


HAWSERresult
sqs_string_from_id(char **pString, const SQS_ID * const id)
{
	static char staticOutput[SQS_ID_BYTES];

	REQUIRE_NOT_NULL(pString);
	REQUIRE_NOT_NULL(id);

	if (*pString == NULL) {
		*pString = staticOutput;
	}

	strncpy(*pString, id->queue_name, SQS_ID_BYTES);

	return HAWSER_OK;
}
