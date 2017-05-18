#include <check.h>
#include <stdlib.h>
#include <string.h>


#include "hawser/hawser.h"
#include "hawser/info.h"


typedef struct {
	AWS_SERVICE service;
	AWS_REGION region;
	const char *expected;
} ENDPOINT_TEST;


static const ENDPOINT_TEST ENDPOINT_TESTS[] = {
	{
		AWS_SERVICE_EC2,
		AWS_REGION_EU_WEST_1,
		"ec2.eu-west-1.amazonaws.com"
	},
	{
		AWS_SERVICE_S3,
		AWS_REGION_US_EAST_1,
		"s3.dualstack.us-east-1.amazonaws.com"
	}
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


START_TEST(test_endpoint_starts_with_service)
{
	AWS_SERVICE service;
	AWS_REGION region;
	HAWSERresult result;
	const char *service_name;
	size_t cbService;
	const char *endpoint;

	for (service = AWS_SERVICE_MIN; service <= AWS_SERVICE_MAX; service += 1) {
		result = aws_service(service, &service_name);
		ck_assert_int_eq(HAWSER_OK, result);
		cbService = strlen(service_name);

		for (region = AWS_REGION_MIN; region <= AWS_REGION_MAX; region += 1) {
			result = aws_endpoint(service, region, &endpoint);

			if (result == HAWSER_BAD_REGION) {
				/* Skip if not supported */
				continue;
			}

			ck_assert_int_eq(0, memcmp(service_name, endpoint, cbService));
		}
	}
}
END_TEST


START_TEST(test_endpoint_contains_region)
{
	AWS_SERVICE service;
	AWS_REGION region;
	HAWSERresult result;
	const char *region_name;
	const char *endpoint;

	for (service = AWS_SERVICE_MIN; service <= AWS_SERVICE_MAX; service += 1) {
		for (region = AWS_REGION_MIN; region <= AWS_REGION_MAX; region += 1) {
			result = aws_region(region, &region_name);
			ck_assert_int_eq(HAWSER_OK, result);

			result = aws_endpoint(service, region, &endpoint);

			if (result == HAWSER_BAD_REGION) {
				/* Skip if not supported */
				continue;
			}

			ck_assert_ptr_ne(NULL, strstr(endpoint, region_name));
		}
	}
}
END_TEST


START_TEST(test_endpoint_ends_correctly)
{
	const char *expected = ".amazonaws.com";
	size_t cbExpected = strlen(expected);
	AWS_SERVICE service;
	AWS_REGION region;
	HAWSERresult result;
	const char *endpoint;
	size_t cbEndpoint;

	for (service = AWS_SERVICE_MIN; service <= AWS_SERVICE_MAX; service += 1) {
		for (region = AWS_REGION_MIN; region <= AWS_REGION_MAX; region += 1) {
			result = aws_endpoint(service, region, &endpoint);

			if (result == HAWSER_BAD_REGION) {
				/* Skip if not supported */
				continue;
			}

			cbEndpoint = strlen(endpoint);
			ck_assert_int_eq(0, memcmp(
				expected,
				endpoint + cbEndpoint - cbExpected,
				cbExpected + 1  /* Include NUL */
			));
		}
	}
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


START_TEST(test_endpoint_bad_region)
{
	HAWSERresult result;
	const char *dest;

	result = aws_endpoint(AWS_SERVICE_LAMBDA, AWS_REGION_CA_CENTRAL_1, &dest);
	ck_assert_int_eq(HAWSER_BAD_REGION, result);
}
END_TEST


Suite *
make_endpoints_suite(void)
{
	static Suite *s;
	TCase *tc_core;

	s = suite_create("endpoints");
	tc_core = tcase_create("Core");

	tcase_add_loop_test(tc_core, test_endpoint_valid, 0, N_ENDPOINT_TESTS);
	tcase_add_test(tc_core, test_endpoint_starts_with_service);
	tcase_add_test(tc_core, test_endpoint_contains_region);
	tcase_add_test(tc_core, test_endpoint_ends_correctly);
	tcase_add_test(tc_core, test_endpoint_invalid_service);
	tcase_add_test(tc_core, test_endpoint_invalid_region);
	tcase_add_test(tc_core, test_endpoint_null_dest);
	tcase_add_test(tc_core, test_endpoint_bad_region);

	suite_add_tcase(s, tc_core);
	return s;
}
