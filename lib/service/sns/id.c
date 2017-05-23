#include <string.h>

#include "hawser/hawser.h"
#include "hawser/service/sns.h"

#include "../../hawser_internal.h"
#include "../id.h"


/**
 * Minimum characters in an SNS ID string.
 */
#define ID_MIN_STRLEN 1


/**
 * Maximum characters in an SNS ID string.
 */
#define ID_MAX_STRLEN 256


HAWSERresult
sns_id_from_string (SNS_ID *id, const char *string)
{
	REQUIRE_NOT_NULL(id);
	REQUIRE_NOT_NULL(string);

	return id_checked_copy(
		id->topic_name,
		string,
		ID_MIN_STRLEN,
		ID_MAX_STRLEN,
		NULL
	);
}


HAWSERresult
sns_string_from_id(char **pString, const SNS_ID * const id)
{
	static char staticOutput[SNS_ID_BYTES];

	REQUIRE_NOT_NULL(pString);
	REQUIRE_NOT_NULL(id);

	if (*pString == NULL) {
		*pString = staticOutput;
	}

	strncpy(*pString, id->topic_name, SNS_ID_BYTES);

	return HAWSER_OK;
}
