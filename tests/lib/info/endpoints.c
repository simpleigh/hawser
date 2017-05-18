#include <check.h>
#include <stdlib.h>

#include "hawser/hawser.h"
#include "hawser/info.h"


typedef struct {
	AWS_SERVICE service;
	AWS_REGION region;
	const char *expected;
} ENDPOINT_TEST;


static const ENDPOINT_TEST ENDPOINT_TESTS[] = {
	{ SERVICE_EC2, AWS_EU_WEST_1, "ec2.eu-west-1.amazonaws.com"          },
	{ SERVICE_S3,  AWS_US_EAST_1, "s3.dualstack.us-east-1.amazonaws.com" }
};


static const size_t N_ENDPOINT_TESTS =
	sizeof(ENDPOINT_TESTS) / sizeof(ENDPOINT_TEST);


START_TEST(test_endpoint_valid)
{
	ENDPOINT_TEST test = ENDPOINT_TESTS[_i];
	const char *dest;
	HAWSERresult result;

	result = aws_endpoint(test.service, test.region, &dest);

	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq(test.expected, dest);
}
END_TEST


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


Suite *
make_endpoints_suite(void)
{
	static Suite *s;
	TCase *tc_core;

	s = suite_create("endpoints");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_endpoint_invalid_service);
	tcase_add_test(tc_core, test_endpoint_invalid_region);
	tcase_add_test(tc_core, test_endpoint_null_dest);
	tcase_add_loop_test(tc_core, test_endpoint_valid, 0, N_ENDPOINT_TESTS);

	suite_add_tcase(s, tc_core);
	return s;
}
