#include <check.h>
#include <stdlib.h>

#include "hawser/hawser.h"
#include "hawser/info.h"


typedef struct {
	AWS_REGION region;
	const char *expected;
} REGION_TEST;


static const REGION_TEST REGION_TESTS[] = {
	{ AWS_REGION_US_EAST_2,       "us-east-2"      },
	{ AWS_REGION_US_EAST_1,       "us-east-1"      },
	{ AWS_REGION_US_WEST_1,       "us-west-1"      },
	{ AWS_REGION_US_WEST_2,       "us-west-2"      },
	{ AWS_REGION_CA_CENTRAL_1,    "ca-central-1"   },
	{ AWS_REGION_AP_SOUTH_1,      "ap-south-1"     },
	{ AWS_REGION_AP_NORTHEAST_2,  "ap-northeast-2" },
	{ AWS_REGION_AP_SOUTHEAST_1,  "ap-southeast-1" },
	{ AWS_REGION_AP_SOUTHEAST_2,  "ap-southeast-2" },
	{ AWS_REGION_AP_NORTHEAST_1,  "ap-northeast-1" },
	{ AWS_REGION_EU_CENTRAL_1,    "eu-central-1"   },
	{ AWS_REGION_EU_WEST_1,       "eu-west-1"      },
	{ AWS_REGION_EU_WEST_2,       "eu-west-2"      },
	{ AWS_REGION_SA_EAST_1,       "sa-east-1"      }
};


static const size_t N_REGION_TESTS =
	sizeof(REGION_TESTS) / sizeof(REGION_TEST);


START_TEST(test_region_valid)
{
	REGION_TEST test = REGION_TESTS[_i];
	HAWSERresult result;
	const char *dest;

	result = aws_region(test.region, &dest);

	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq(test.expected, dest);
}
END_TEST


START_TEST(test_region_invalid_region)
{
	HAWSERresult result;
	const char *dest;

	result = aws_region(AWS_REGION_MIN - 1, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);

	result = aws_region(AWS_REGION_MAX + 1, &dest);
	ck_assert_int_eq(HAWSER_INVALID, result);
}
END_TEST


START_TEST(test_region_null_dest)
{
	HAWSERresult result;

	result = aws_region(AWS_REGION_MIN, (const char **)NULL);
	ck_assert_int_eq(HAWSER_NULL, result);
}
END_TEST


TCase *
tcase_info_regions(void)
{
	static TCase *tc;
	tc = tcase_create("regions");

	tcase_add_loop_test(tc, test_region_valid, 0, N_REGION_TESTS);
	tcase_add_test(tc, test_region_invalid_region);
	tcase_add_test(tc, test_region_null_dest);

	return tc;
}
