#include "hawser/hawser.h"
#include "hawser/s3.h"

#include "../hawser_internal.h"
#include "../id.h"


/**
 * Minimum characters in an S3 ID string.
 */
#define ID_MIN_STRLEN 3


/**
 * Maximum characters in an S3 ID string.
 */
#define ID_MAX_STRLEN 63


/**
 * Checks whether ID characters are valid.
 */
static BOOL
is_valid_id_char(char current, char previous)
{
	if (FALSE
		|| (current >= 'a' && current <= 'z')
		|| (current >= '0' && current <= '9')
		|| (current == '-'
			&& previous != '\0' && previous != '.')
		|| (current == '.'
			&& previous != '\0' && previous != '.' && previous != '-')
		|| (current == '\0'
			&& previous != '.' && previous != '-')
	) {
		return TRUE;
	}

	return FALSE;
}


HAWSERresult
s3_id_from_string (S3_ID *id, const char *string)
{
	REQUIRE_NOT_NULL(id);
	REQUIRE_NOT_NULL(string);

	return id_checked_copy(
		id->bucket_name,
		string,
		ID_MIN_STRLEN,
		ID_MAX_STRLEN,
		&is_valid_id_char
	);
}
