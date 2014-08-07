#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Env {
	const char *name;
	char *destination;
	size_t length;
} Env;

const Env ENV[] = {
	{ "AWS_ACCESS_KEY_ID",     credentials.access_key_id,     20 },
	{ "AWS_SECRET_ACCESS_KEY", credentials.secret_access_key, 40 }
};

void
credentials_load_environment()
{
	size_t cFields = sizeof(ENV) / sizeof(Env);
	size_t i;
	char *source;

	for (i = 0; i < cFields; i++) {
		source = getenv(ENV[i].name);
		if (source != NULL) {
			memcpy(ENV[i].destination, source, ENV[i].length);
			ENV[i].destination[ENV[i].length] = '\0';
		}
	}
}

int main(void)
{
	credentials_load_environment();
	printf("Access Key ID: %s\n",     credentials_get_access_key_id());
	printf("Secret access key: %s\n", credentials_get_secret_access_key());
	return 0;
}
