#include <check.h>

#include "info.h"


Suite *
suite_info(void)
{
	static Suite *s;
	s = suite_create("info");

	suite_add_tcase(s, tcase_info_endpoints());
	suite_add_tcase(s, tcase_info_regions());
	suite_add_tcase(s, tcase_info_services());

	return s;
}
