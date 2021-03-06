#include <check.h>
#include <stdlib.h>

#include "service/ec2.h"
#include "service/lambda.h"
#include "service/s3.h"
#include "service/sns.h"
#include "service/sqs.h"
#include "encodings.h"
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
	srunner_add_suite(sr, suite_lambda());
	srunner_add_suite(sr, suite_s3());
	srunner_add_suite(sr, suite_sns());
	srunner_add_suite(sr, suite_sqs());
	srunner_add_suite(sr, suite_encodings());
	srunner_add_suite(sr, suite_info());

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
