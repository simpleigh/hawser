#include <getopt.h>
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

const struct option OPTIONS[] = {
	{ "access-key-id",     required_argument, NULL, 0 },
	{ "secret-access-key", required_argument, NULL, 0 },
	{ NULL,                0,                 NULL, 0 }
};

typedef struct Option {
	char *destination;
	size_t length;
} Option;

const Option OPTS[] = {
	{ credentials.access_key_id,     20 },
	{ credentials.secret_access_key, 40 }
};

void
credentials_load_command_line(int argc, char **argv)
{
	int c;

	while (1) {
		int option_index = 0;
		c = getopt_long(argc, argv, "", OPTIONS, &option_index);
		if (c == -1) {
			break;
		}

		memcpy(OPTS[option_index].destination, optarg, OPTS[option_index].length);
		OPTS[option_index].destination[OPTS[option_index].length] = '\0';
	}
}

int main(int argc, char **argv)
{
	credentials_load_environment();
	credentials_load_command_line(argc, argv);
	printf("Access Key ID: %s\n",     credentials_get_access_key_id());
	printf("Secret access key: %s\n", credentials_get_secret_access_key());
	return 0;
}
