#include <check.h>

#include "hawser/hawser.h"
#include "hawser/service/s3.h"


static const char * VALID_IDS[] = {
	"bucket",
	"123",
	"123456789012345678901234567890123456789012345678901234567890123",
	"abcdefghijklmnopqrstuvwxyz",
	"0123456789",
	"label1.label2",
	"label1-label2"
};


static const size_t N_VALID_IDS = sizeof(VALID_IDS) / sizeof(char *);


static const char * INVALID_IDS[] = {
	"12",
	"1234567890123456789012345678901234567890123456789012345678901234",
	"_",
	"/",
	".label1.label2",
	"label1..label2",
	"label1.label2.",
	"-label1.label2",
	"label1-.label2",
	"label1.-label2",
	"label1.label2-"
};


static const size_t N_INVALID_IDS = sizeof(INVALID_IDS) / sizeof(char *);


START_TEST(test_valid_ids)
{
	S3_ID id;
	HAWSERresult result;

	result = s3_id_from_string(&id, VALID_IDS[_i]);
	ck_assert_int_eq(HAWSER_OK, result);
}
END_TEST


START_TEST(test_id_populated)
{
	S3_ID id;

	s3_id_from_string(&id, VALID_IDS[_i]);
	ck_assert_str_eq(VALID_IDS[_i], id.bucket_name);
}
END_TEST


START_TEST(test_invalid_ids)
{
	S3_ID id;
	HAWSERresult result;

	result = s3_id_from_string(&id, INVALID_IDS[_i]);
	ck_assert_int_eq(HAWSER_INVALID, result);
}
END_TEST


START_TEST(test_null_id)
{
	ck_assert_int_eq(HAWSER_NULL, s3_id_from_string(NULL, VALID_IDS[0]));
}
END_TEST


START_TEST(test_null_string)
{
	S3_ID id;
	ck_assert_int_eq(HAWSER_NULL, s3_id_from_string(&id, NULL));
}
END_TEST


TCase *
tcase_s3_id(void)
{
	static TCase *tc;
	tc = tcase_create("id");

	tcase_add_loop_test(tc, test_valid_ids, 0, N_VALID_IDS);
	tcase_add_loop_test(tc, test_invalid_ids, 0, N_INVALID_IDS);
	tcase_add_loop_test(tc, test_id_populated, 0, N_VALID_IDS);
	tcase_add_test(tc, test_null_id);
	tcase_add_test(tc, test_null_string);

	return tc;
}
