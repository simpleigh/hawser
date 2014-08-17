#include <string.h>

#include "config.h"

typedef struct Config {
	char access_key_id[21];
	char secret_access_key[41];
} Config;

static Config config = { "", "" };

const char *
config_get_access_key_id()
{
	return config.access_key_id;
}

const char *
config_get_secret_access_key()
{
	return config.secret_access_key;
}

void
config_set(char *dest, const char *src, size_t len)
{
	if (src == NULL) {
		return;
	}

	/* Check length. */
	if ((const char *)memchr(src, '\0', len + 1) != src + len) {
		return;
	}

	memcpy(dest, src, len);
	dest[len] = '\0';
}

void
config_set_access_key_id(const char *src)
{
	config_set(config.access_key_id, src, 20);
}

void
config_set_secret_access_key(const char *src)
{
	config_set(config.secret_access_key, src, 40);
}

void
config_load(int argc, char **argv)
{
	config_load_iam();
	config_load_file("/etc/hawser");
	config_load_user_file();
	config_load_environment();
	config_load_arguments(argc, argv);
}
