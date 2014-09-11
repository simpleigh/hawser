#include <check.h>
#include <stdlib.h>

#include "hawser/hawser.h"
#include "hawser/ec2.h"

START_TEST(test_read_error_if_pointers_null)
{
	EC2_ID id;
	const char *string = "i-12345678";

	ck_assert_int_eq(HAWSER_NULL, ec2_ptoid((EC2_ID *)NULL, string));
	ck_assert_int_eq(HAWSER_NULL, ec2_ptoid(&id, (const char *)NULL));
}
END_TEST

const char * const INVALID_IDS[] = {
	"1234567890123456", /* too long      */
	"123456789",        /* too short     */
	"1234567890",       /* no hyphen     */
	"-123456789",       /* tag too short */
	"1234567-12"        /* tag too long  */
	"12-1234567",       /* ID too short  */
	"1-123456789",      /* ID too long   */
	"notag-12345678",   /* unknown tag   */
	"i-1234567/",       /* invalid char  */
	"i-1234567:",       /* invalid char  */
	"i-1234567`",       /* invalid char  */
	"i-1234567g"        /* invalid char  */
};

START_TEST(test_read_errors)
{
	EC2_ID id;
	const char *string = INVALID_IDS[_i];

	ck_assert_int_eq(HAWSER_INVALID, ec2_ptoid(&id, string));
}
END_TEST

int
main()
{
	Suite *s = suite_create("lib/ec2/id");
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
