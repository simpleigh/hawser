#include <check.h>
#include <stdlib.h>

#include "hawser/hawser.h"
#include "hawser/info.h"


START_TEST(test_endpoint_invalid_service)
{
	HAWSERresult result;
	const char *dest;

	result = aws_endpoint(AWS_SERVICE_MIN - 1, AWS_REGION_MIN, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);

	result = aws_endpoint(AWS_SERVICE_MAX + 1, AWS_REGION_MIN, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);
}
END_TEST


START_TEST(test_endpoint_invalid_region)
{
	HAWSERresult result;
	const char *dest;

	result = aws_endpoint(AWS_SERVICE_MIN, AWS_REGION_MIN - 1, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);

	result = aws_endpoint(AWS_SERVICE_MIN, AWS_REGION_MAX + 1, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);
}
END_TEST


START_TEST(test_endpoint_null_dest)
{
	HAWSERresult result;

	result = aws_endpoint(AWS_SERVICE_MIN, AWS_REGION_MIN, (const char **)NULL);
	ck_assert_int_eq(HAWSER_NULL, result);
}
END_TEST


int
main()
{
	Suite *s = suite_create("lib/info/endpoints");
	TCase *tc_core = tcase_create("Core");
	SRunner *sr;
	int number_failed;

	tcase_add_test(tc_core, test_endpoint_invalid_service);
	tcase_add_test(tc_core, test_endpoint_invalid_region);
	tcase_add_test(tc_core, test_endpoint_null_dest);

	suite_add_tcase(s, tc_core);
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
