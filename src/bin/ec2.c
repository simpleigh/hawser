#include "../lib/buffer.h"
#include "../lib/encodings.h"

#include <openssl/hmac.h>
#include <stdio.h>
#include <string.h>

int main()
{
	const EVP_MD *sha256 = EVP_sha256();
	char *key = "AWS4wJalrXUtnFEMI/K7MDENG+bPxRfiCYEXAMPLEKEY";
	char *date = "20110909";
	char *region = "us-east-1";
	char *service = "iam";
	char *end = "aws4_request";
	unsigned char *result; /* 32 bytes */
	unsigned int length;
	char *string_to_sign = "AWS4-HMAC-SHA256\n20110909T233600Z\n20110909/us-east-1/iam/aws4_request\n3511de7e95d28ecd39e9513b642aee07e54f4941150d8df8bf94b328ef7e55e2";
	size_t i;
	BUFFER *bufOut = buffer_create();

	result = HMAC(
		sha256,
		(unsigned char *)key,
		strlen(key),
		(unsigned char *)date,
		strlen(date),
		NULL,
		&length
	);

	result = HMAC(
		sha256,
		result,
		length,
		(unsigned char *)region,
		strlen(region),
		NULL,
		NULL
	);

	result = HMAC(
		sha256,
		result,
		length,
		(unsigned char *)service,
		strlen(service),
		NULL,
		NULL
	);

	result = HMAC(
		sha256,
		result,
		length,
		(unsigned char *)end,
		strlen(end),
		NULL,
		NULL
	);

	puts("Sample signing key:");
	for (i = 0; i < length; i++) {
		printf("%u ", result[i]);
	}
	printf("\n");

	result = HMAC(
		sha256,
		result,
		length,
		(unsigned char *)string_to_sign,
		strlen(string_to_sign),
		NULL,
		NULL
	);

	puts("Signature:");
	encode_base16(bufOut, (const char *)result, length);
	puts(buffer_data(bufOut));
	buffer_destroy(bufOut);

	return 0;
}
