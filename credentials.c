#include <stdio.h>

typedef struct Credentials {
	char access_key_id[21];
	char secret_access_key[41];
} Credentials;

static Credentials credentials = { "", "" };

const char *
credentials_get_access_key_id()
{
	return credentials.access_key_id;
}

const char *
credentials_get_secret_access_key()
{
	return credentials.secret_access_key;
}

int main(void)
{
	printf("Access Key ID: %s\n",     credentials_get_access_key_id());
	printf("Secret access key: %s\n", credentials_get_secret_access_key());
	return 0;
}
