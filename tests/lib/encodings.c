#include <check.h>
#include <stddef.h>

#include "hawser/hawser.h"

#include "../../lib/buffer.h"
#include "../../lib/encodings.h"

#include "encodings.h"


typedef struct {
	const char *szInput;
	size_t cbInput;
	const char *szExpected;
} ENCODING_TEST;


static const ENCODING_TEST BASE16_TESTS[] = {
	{ "",       0, ""            },
	{ "f",      1, "66"          },
	{ "fo",     2, "666f"        },
	{ "foo",    3, "666f6f"      },
	{ "foob",   4, "666f6f62"    },
	{ "fooba",  5, "666f6f6261"  },
	{ "foobar", 6, "666f6f626172"},
	{ "/",      1, "2f"          }
};


static const size_t N_BASE16_TESTS =
	sizeof(BASE16_TESTS) / sizeof(ENCODING_TEST);


START_TEST(test_base16)
{
	BUFFER *buffer = buffer_create();
	HAWSERresult result;

	result = encode_base16(
		buffer,
		BASE16_TESTS[_i].szInput,
		BASE16_TESTS[_i].cbInput
	);

	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq(BASE16_TESTS[_i].szExpected, buffer_data(buffer));

	buffer_destroy(buffer);
}
END_TEST


START_TEST(test_base16_buffer_null)
{
	ck_assert_int_eq(HAWSER_NULL, encode_base16(NULL, "", 0));
}
END_TEST


START_TEST(test_base16_string_null)
{
	BUFFER *buffer = buffer_create();
	ck_assert_int_eq(HAWSER_NULL, encode_base16(buffer, NULL, 0));
	buffer_destroy(buffer);
}
END_TEST


static const ENCODING_TEST URI_TESTS[] = {
	{ "",       0, ""       },
	{ "f",      1, "f"      },
	{ "fo",     2, "fo"     },
	{ "foo",    3, "foo"    },
	{ "foob",   4, "foob"   },
	{ "fooba",  5, "fooba"  },
	{ "foobar", 6, "foobar" },
	{ "/",      1, "%2f"    }
};


static const size_t N_URI_TESTS =
	sizeof(URI_TESTS) / sizeof(ENCODING_TEST);


START_TEST(test_uri)
{
	BUFFER *buffer = buffer_create();
	HAWSERresult result;

	result = encode_uri(
		buffer,
		URI_TESTS[_i].szInput,
		URI_TESTS[_i].cbInput
	);

	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq(URI_TESTS[_i].szExpected, buffer_data(buffer));

	buffer_destroy(buffer);
}
END_TEST


START_TEST(test_uri_buffer_null)
{
	ck_assert_int_eq(HAWSER_NULL, encode_uri(NULL, "", 0));
}
END_TEST


START_TEST(test_uri_string_null)
{
	BUFFER *buffer = buffer_create();
	ck_assert_int_eq(HAWSER_NULL, encode_uri(buffer, NULL, 0));
	buffer_destroy(buffer);
}
END_TEST


TCase *
tcase_encodings(void)
{
	static TCase *tc;
	tc = tcase_create("encodings");

	tcase_add_loop_test(tc, test_base16, 0, N_BASE16_TESTS);
	tcase_add_test(tc, test_base16_buffer_null);
	tcase_add_test(tc, test_base16_string_null);
	tcase_add_loop_test(tc, test_uri, 0, N_URI_TESTS);
	tcase_add_test(tc, test_uri_buffer_null);
	tcase_add_test(tc, test_uri_string_null);

	return tc;
}


Suite *
suite_encodings(void)
{
	static Suite *s;
	s = suite_create("encodings");

	suite_add_tcase(s, tcase_encodings());

	return s;
}
