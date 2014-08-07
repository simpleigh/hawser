#include "../credentials.h"

#include <stdlib.h>
#include <string.h>

typedef struct Env {
	const char *name;
	void (*store)(char *);
} Env;

const Env ENV[] = {
	{ "AWS_ACCESS_KEY_ID",     credentials_set_access_key_id     },
	{ "AWS_SECRET_ACCESS_KEY", credentials_set_secret_access_key }
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
			ENV[i].store(source);
		}
	}
}
