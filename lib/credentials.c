#include "credentials.h"

#include <string.h>

typedef struct Credentials {
	char access_key_id[21];
	char secret_access_key[41];
} Credentials;

Credentials credentials = { "", "" };

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

void
credentials_set(char *dest, const char *src, size_t len)
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
credentials_set_access_key_id(const char *src)
{
	credentials_set(credentials.access_key_id, src, 20);
}

void
credentials_set_secret_access_key(const char *src)
{
	credentials_set(credentials.secret_access_key, src, 40);
}
