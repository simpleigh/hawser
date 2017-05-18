#include <check.h>
#include <stdlib.h>

#include "ec2.h"
#include "info.h"


Suite *
suite_empty(void)
{
	static Suite *s;
	s = suite_create("empty");
	return s;
}


int
main()
{
	SRunner *sr;
	int number_failed;

	sr = srunner_create(suite_empty());
	srunner_add_suite(sr, suite_ec2());
	srunner_add_suite(sr, suite_info());

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
