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

const char * const INVALID_IDS[] = {
	"subnet-12345678a", /* too long      */
	"i12345678",        /* no tag        */
	"-12345678",        /* tag too short */
	"subneta-1234567"   /* tag too long  */
	"i-1234567",        /* ID too short  */
	"i-123456789",      /* ID too long   */
	"notag-12345678"    /* unknown tag   */
};

START_TEST(test_read_errors)
{
	HAWSER_EC2_RESOURCE_ID resourceId;
	const char *string = INVALID_IDS[_i];

	ck_assert_int_eq(HAWSER_INVALID, hawser_ec2_id_read(&resourceId, string));
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
	tcase_add_loop_test(tc_core, test_read_errors, 0, sizeof(INVALID_IDS) / sizeof (char *));

	suite_add_tcase(s, tc_core);
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
