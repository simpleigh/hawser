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


START_TEST(test_read_valid_ids)
{
	S3_ID id;
	HAWSERresult result;

	result = s3_id_from_string(&id, VALID_IDS[_i]);
	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq(VALID_IDS[_i], id.bucket_name);
}
END_TEST


START_TEST(test_read_invalid_ids)
{
	S3_ID id;
	HAWSERresult result;

	result = s3_id_from_string(&id, INVALID_IDS[_i]);
	ck_assert_int_eq(HAWSER_INVALID, result);
}
END_TEST


START_TEST(test_read_null_id)
{
	ck_assert_int_eq(HAWSER_NULL, s3_id_from_string(NULL, VALID_IDS[0]));
}
END_TEST


START_TEST(test_read_null_string)
{
	S3_ID id;
	ck_assert_int_eq(HAWSER_NULL, s3_id_from_string(&id, NULL));
}
END_TEST


START_TEST(test_write_static_memory)
{
	S3_ID id;
	char *string = NULL;

	ck_assert_int_eq(HAWSER_OK, s3_id_from_string(&id, VALID_IDS[_i]));
	ck_assert_int_eq(HAWSER_OK, s3_string_from_id(&string, &id));
	ck_assert_str_eq(VALID_IDS[_i], string);
}
END_TEST


START_TEST(test_write_supplied_memory)
{
	S3_ID id;
	char aString[S3_ID_BYTES];
	char *szString = aString;

	ck_assert_int_eq(HAWSER_OK, s3_id_from_string(&id, VALID_IDS[_i]));
	ck_assert_int_eq(HAWSER_OK, s3_string_from_id(&szString, &id));
	ck_assert_str_eq(VALID_IDS[_i], szString);
}
END_TEST


START_TEST(test_write_null_string)
{
	S3_ID id;
	ck_assert_int_eq(HAWSER_NULL, s3_string_from_id(NULL, &id));
}
END_TEST


START_TEST(test_write_null_id)
{
	char *string;
	ck_assert_int_eq(HAWSER_NULL, s3_string_from_id(&string, NULL));
}
END_TEST


TCase *
tcase_s3_id(void)
{
	static TCase *tc;
	tc = tcase_create("id");

	tcase_add_loop_test(tc, test_read_valid_ids, 0, N_VALID_IDS);
	tcase_add_loop_test(tc, test_read_invalid_ids, 0, N_INVALID_IDS);
	tcase_add_test(tc, test_read_null_id);
	tcase_add_test(tc, test_read_null_string);
	tcase_add_test(tc, test_write_null_string);
	tcase_add_test(tc, test_write_null_id);
	tcase_add_loop_test(tc, test_write_static_memory, 0, N_VALID_IDS);
	tcase_add_loop_test(tc, test_write_supplied_memory, 0, N_VALID_IDS);

	return tc;
}
