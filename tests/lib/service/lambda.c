#include <check.h>

#include "lambda.h"


Suite *
suite_lambda(void)
{
	static Suite *s;
	s = suite_create("lambda");

	suite_add_tcase(s, tcase_lambda_id());

	return s;
}
