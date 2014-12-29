#include <check.h>
#include <stdlib.h>

#include "info.h"

int
main()
{
	SRunner *sr;
	int number_failed;

	sr = srunner_create(make_endpoints_suite());

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}