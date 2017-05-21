#include <check.h>
#include <stdlib.h>

#include "hawser/hawser.h"
#include "hawser/service/ec2.h"


typedef struct {
	EC2_RT type;
	const char *tag;
} RT_ROW;


static const RT_ROW RESOURCE_TYPES[] = {
	{ EC2_CUSTOMER_GATEWAY,       "cgw"    },
	{ EC2_INSTANCE,               "i"      },
	{ EC2_SUBNET,                 "subnet" },
	{ EC2_VPN_GATEWAY,            "vgw"    }
};


static const size_t N_RESOURCE_TYPES = sizeof(RESOURCE_TYPES) / sizeof(RT_ROW);


START_TEST(test_ptoid_valid)
{
	RT_ROW type = RESOURCE_TYPES[_i];
	EC2_ID id;
	char input[EC2_ID_MAX_BYTES];
	HAWSERresult result;

	input[0] = '\0';
	strcat(input, type.tag);
	strcat(input, "-12345678");

	result = ec2_ptoid(&id, input);

	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_int_eq(type.type, id.resourceType);
	ck_assert_str_eq("12345678", id.id);
}
END_TEST


START_TEST(test_ptoid_valid_chars)
{
	EC2_ID id;
	HAWSERresult result;

	result = ec2_ptoid(&id, "i-12345678");
	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq("12345678", id.id);

	result = ec2_ptoid(&id, "i-90abcdef");
	ck_assert_int_eq(HAWSER_OK, result);
	ck_assert_str_eq("90abcdef", id.id);
}
END_TEST


static const char * const INVALID_STRINGS[] = {
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


static const size_t N_INVALID_STRINGS =
	sizeof(INVALID_STRINGS) / sizeof(char *);


START_TEST(test_ptoid_invalid)
{
	EC2_ID id;
	const char *string = INVALID_STRINGS[_i];

	ck_assert_int_eq(HAWSER_INVALID, ec2_ptoid(&id, string));
}
END_TEST


START_TEST(test_ptoid_null)
{
	EC2_ID id;
	const char *string = "i-12345678";

	ck_assert_int_eq(HAWSER_NULL, ec2_ptoid((EC2_ID *)NULL, string));
	ck_assert_int_eq(HAWSER_NULL, ec2_ptoid(&id, (const char *)NULL));
}
END_TEST


START_TEST(test_idtop_valid)
{
	RT_ROW type = RESOURCE_TYPES[_i];
	size_t cbTag = strlen(type.tag);
	EC2_ID id;
	char output[EC2_ID_MAX_BYTES];
	char *result;

	id.resourceType = type.type;
	strcpy(id.id, "12345678");

	result = ec2_idtop(output, &id);

	ck_assert_ptr_eq(output, result);
	ck_assert_str_eq("-12345678", output + cbTag);

	output[cbTag] = '\0';
	ck_assert_str_eq(type.tag, output);
}
END_TEST


START_TEST(test_idtop_valid_static)
{
	RT_ROW type = RESOURCE_TYPES[_i];
	EC2_ID id;
	char output1[EC2_ID_MAX_BYTES];
	char *output2;

	id.resourceType = type.type;
	strcpy(id.id, "12345678");

	ec2_idtop(output1, &id);
	output2 = ec2_idtop((char *)NULL, &id);

	ck_assert_str_eq(output1, output2);
}
END_TEST


static const EC2_ID INVALID_IDS[] = {
	{ EC2_RT_MIN - 1, "12345678"  },
	{ EC2_RT_MAX + 1, "12345678"  },
	{ EC2_IMAGE,      "123456789" },
	{ EC2_IMAGE,      "1234567/"  },
	{ EC2_IMAGE,      "1234567:"  },
	{ EC2_IMAGE,      "1234567`"  },
	{ EC2_IMAGE,      "1234567g"  }
};


static const size_t N_INVALID_IDS = sizeof(INVALID_IDS) / sizeof(EC2_ID);


START_TEST(test_idtop_invalid)
{
	EC2_ID id = INVALID_IDS[_i];
	char *output = ec2_idtop((char *)NULL, &id);
	ck_assert_ptr_eq(NULL, output);
}
END_TEST


START_TEST(test_idtop_null)
{
	char *output = ec2_idtop((char *)NULL, (EC2_ID *)NULL);
	ck_assert_ptr_eq(NULL, output);
}
END_TEST


TCase *
tcase_ec2_id(void)
{
	static TCase *tc;
	tc = tcase_create("id");

	tcase_add_loop_test(tc, test_ptoid_valid, 0, N_RESOURCE_TYPES);
	tcase_add_test(tc, test_ptoid_valid_chars);
	tcase_add_loop_test(tc, test_ptoid_invalid, 0, N_INVALID_STRINGS);
	tcase_add_test(tc, test_ptoid_null);

	tcase_add_loop_test(tc, test_idtop_valid,        0, N_RESOURCE_TYPES);
	tcase_add_loop_test(tc, test_idtop_valid_static, 0, N_RESOURCE_TYPES);
	tcase_add_loop_test(tc, test_idtop_invalid,      0, N_INVALID_IDS);
	tcase_add_test(tc, test_idtop_null);

	return tc;
}
