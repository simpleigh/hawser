#include <check.h>

#include "ec2.h"


Suite *
suite_ec2(void)
{
	static Suite *s;
	s = suite_create("ec2");

	suite_add_tcase(s, tcase_ec2_id());

	return s;
}
