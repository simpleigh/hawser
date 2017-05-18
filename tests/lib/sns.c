#include <check.h>

#include "sns.h"


Suite *
suite_sns(void)
{
	static Suite *s;
	s = suite_create("sns");

	suite_add_tcase(s, tcase_sns_id());

	return s;
}
