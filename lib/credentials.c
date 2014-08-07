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
credentials_set_access_key_id(const char *src)
{
	if (src == NULL) {
		return;
	}
	memcpy(credentials.access_key_id, src, 20);
	credentials.access_key_id[20] = '\0';
}

void
credentials_set_secret_access_key(const char *src)
{
	if (src == NULL) {
		return;
	}
	memcpy(credentials.secret_access_key, src, 40);
	credentials.secret_access_key[40] = '\0';
}
