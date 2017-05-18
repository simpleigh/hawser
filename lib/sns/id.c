#include "hawser/hawser.h"
#include "hawser/sns.h"

#include "../hawser_internal.h"
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
