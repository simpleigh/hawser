#include <check.h>

#include "hawser/hawser.h"
#include "hawser/service/sns.h"


static const char * VALID_IDS[] = {
	"topic",
	(
		"123456789012345678901234567890123456789012345678901234567890"
		"123456789012345678901234567890123456789012345678901234567890"
		"123456789012345678901234567890123456789012345678901234567890"
		"123456789012345678901234567890123456789012345678901234567890"
		"1234567890123456"
	),
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	"abcdefghijklmnopqrstuvwxyz",
	"0123456789",
	"_",
	"-"
};


static const size_t N_VALID_IDS = sizeof(VALID_IDS) / sizeof(char *);


static const char * INVALID_IDS[] = {
	"",
	(
		"123456789012345678901234567890123456789012345678901234567890"
		"123456789012345678901234567890123456789012345678901234567890"
		"123456789012345678901234567890123456789012345678901234567890"
		"123456789012345678901234567890123456789012345678901234567890"
		"12345678901234567"
	),
	"/"
};


static const size_t N_INVALID_IDS = sizeof(INVALID_IDS) / sizeof(char *);


START_TEST(test_read_valid_ids)
{
	SNS_ID id;
	HAWSERresult result;

	result = sns_id_from_string(&id, VALID_IDS[_i]);
	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq(VALID_IDS[_i], id.topic_name);
}
END_TEST


START_TEST(test_read_invalid_ids)
{
	SNS_ID id;
	HAWSERresult result;

	result = sns_id_from_string(&id, INVALID_IDS[_i]);
	ck_assert_int_eq(HAWSER_INVALID, result);
}
END_TEST


START_TEST(test_read_null_id)
{
	ck_assert_int_eq(HAWSER_NULL, sns_id_from_string(NULL, VALID_IDS[0]));
}
END_TEST


START_TEST(test_read_null_string)
{
	SNS_ID id;
	ck_assert_int_eq(HAWSER_NULL, sns_id_from_string(&id, NULL));
}
END_TEST


TCase *
tcase_sns_id(void)
{
	static TCase *tc;
	tc = tcase_create("id");

	tcase_add_loop_test(tc, test_read_valid_ids, 0, N_VALID_IDS);
	tcase_add_loop_test(tc, test_read_invalid_ids, 0, N_INVALID_IDS);
	tcase_add_test(tc, test_read_null_id);
	tcase_add_test(tc, test_read_null_string);

	return tc;
}
