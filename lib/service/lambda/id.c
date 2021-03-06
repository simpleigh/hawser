#include <string.h>

#include "hawser/hawser.h"
#include "hawser/service/lambda.h"

#include "../../hawser_internal.h"
#include "../id.h"


/**
 * Minimum characters in a Lambda ID string.
 */
#define ID_MIN_STRLEN 1


/**
 * Maximum characters in a Lambda ID string.
 */
#define ID_MAX_STRLEN 64


HAWSERresult
lambda_id_from_string (LAMBDA_ID *id, const char *string)
{
	REQUIRE_NOT_NULL(id);
	REQUIRE_NOT_NULL(string);

	return id_checked_copy(
		id->function_name,
		string,
		ID_MIN_STRLEN,
		ID_MAX_STRLEN,
		NULL
	);
}


HAWSERresult
lambda_string_from_id(char **pString, const LAMBDA_ID * const id)
{
	static char staticOutput[LAMBDA_ID_BYTES];

	REQUIRE_NOT_NULL(pString);
	REQUIRE_NOT_NULL(id);

	if (*pString == NULL) {
		*pString = staticOutput;
	}

	strncpy(*pString, id->function_name, LAMBDA_ID_BYTES);

	return HAWSER_OK;
}
