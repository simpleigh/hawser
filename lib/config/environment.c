#include <stdlib.h>
#include <string.h>

#include "../config.h"

typedef struct EnvironmentVariable {
	const char *name;
	void (*store)(const char *);
} EnvironmentVariable;

/**
 * List of environment variables to read
 * Maps possible environment variables to the functions used to store them.
 */
static const EnvironmentVariable ENVIRONMENT_VARIABLES[] = {
	{ "AWS_ACCESS_KEY_ID",     config_set_access_key_id     },
	{ "AWS_SECRET_ACCESS_KEY", config_set_secret_access_key },
	{ NULL,                    NULL                              }
};

void
config_load_environment()
{
	const EnvironmentVariable *variable = ENVIRONMENT_VARIABLES;
	char *value;

	while (variable->name) {
		value = getenv(variable->name);
		variable->store(value);
		variable++;
	}
}
