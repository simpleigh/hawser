#include <check.h>

#include "sqs.h"


Suite *
suite_sqs(void)
{
	static Suite *s;
	s = suite_create("sqs");

	suite_add_tcase(s, tcase_sqs_id());

	return s;
}
