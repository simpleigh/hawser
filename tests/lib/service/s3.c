#include <check.h>

#include "s3.h"


Suite *
suite_s3(void)
{
	static Suite *s;
	s = suite_create("s3");

	suite_add_tcase(s, tcase_s3_id());

	return s;
}
