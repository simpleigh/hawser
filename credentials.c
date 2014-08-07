#include <stdio.h>

typedef struct Credentials {
	char access_key_id[21];
	char secret_access_key[41];
} Credentials;

static Credentials credentials = { "", "" };

int main(void)
{
	printf("Access Key ID: %s\n",     credentials.access_key_id);
	printf("Secret access key: %s\n", credentials.secret_access_key);
	return 0;
}
