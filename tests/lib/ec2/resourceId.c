#include <check.h>
#include <stdlib.h>

#include "hawser/hawser.h"
#include "hawser/ec2.h"

START_TEST(test_read_error_if_pointers_null)
{
	HAWSER_EC2_RESOURCE_ID resourceId;
	const char *string = "i-12345678";

	ck_assert_int_eq(
		HAWSER_NULL,
		hawser_ec2_id_read(
			(HAWSER_EC2_RESOURCE_ID *)NULL,
			string
		)
	);
	ck_assert_int_eq(
		HAWSER_NULL,
		hawser_ec2_id_read(
			&resourceId,
			(const char *)NULL
		)
	);
}
END_TEST

int
main()
{
	Suite *s = suite_create("lib/ec2/resourceId");
	TCase *tc_core = tcase_create("Core");
	SRunner *sr;
	int number_failed;

	tcase_add_test(tc_core, test_read_error_if_pointers_null);

	suite_add_tcase(s, tc_core);
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
