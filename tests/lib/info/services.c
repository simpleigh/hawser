#include <check.h>
#include <stdlib.h>

#include "hawser/hawser.h"
#include "hawser/info.h"


typedef struct {
	AWS_SERVICE service;
	const char *expected;
} SERVICE_TEST;


static const SERVICE_TEST SERVICE_TESTS[] = {
	{ AWS_SERVICE_EC2, "ec2" },
	{ AWS_SERVICE_S3,  "s3"  }
};


static const size_t N_SERVICE_TESTS =
	sizeof(SERVICE_TESTS) / sizeof(SERVICE_TEST);


START_TEST(test_service_valid)
{
	SERVICE_TEST test = SERVICE_TESTS[_i];
	HAWSERresult result;
	const char *dest;

	result = aws_service_namespace(test.service, &dest);

	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq(test.expected, dest);
}
END_TEST


START_TEST(test_service_invalid_service)
{
	HAWSERresult result;
	const char *dest;

	result = aws_service_namespace(AWS_SERVICE_MIN - 1, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);

	result = aws_service_namespace(AWS_SERVICE_MAX + 1, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);
}
END_TEST


START_TEST(test_service_null_dest)
{
	HAWSERresult result;

	result = aws_service_namespace(AWS_SERVICE_MIN, (const char **)NULL);
	ck_assert_int_eq(HAWSER_NULL, result);
}
END_TEST


TCase *
tcase_info_services(void)
{
	static TCase *tc;
	tc = tcase_create("services");

	tcase_add_loop_test(tc, test_service_valid, 0, N_SERVICE_TESTS);
	tcase_add_test(tc, test_service_invalid_service);
	tcase_add_test(tc, test_service_null_dest);

	return tc;
}
