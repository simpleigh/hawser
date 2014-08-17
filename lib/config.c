#include <string.h>

#include "buffer.h"
#include "config.h"

Config config = {
	NULL, /* szRegion          */
	"",   /* szAccessKeyId     */
	"",   /* szSecretAccessKey */
	NULL, /* szToken           */
	0,    /* fIamRole          */
	0     /* fDebug            */
};

static void
config_set(char *szDestination, const char *szInput, size_t cbExpected)
{
	const char *pchNil;

	if (szInput == NULL) {
		return;
	}

	/* Check length. */
	pchNil = (const char *)memchr(szInput, '\0', cbExpected + 1);
	if (pchNil != szInput + cbExpected) {
		return;
	}

	memcpy(szDestination, szInput, cbExpected);
	szDestination[cbExpected] = '\0';
}

static const char * const REGIONS[] = {
	"us-east-1",
	"us-west-2",
	"us-west-1",
	"eu-west-1",
	"ap-southeast-1",
	"ap-southeast-2",
	"ap-northeast-1",
	"sa-east-1",
	NULL
};

void
config_set_region(const char *szInput)
{
	size_t iRegions = 0;

	if (szInput == NULL) {
		return;
	}

	while (REGIONS[iRegions]) {
		if (strcmp(szInput, REGIONS[iRegions]) == 0) {
			config.szRegion = REGIONS[iRegions];
			return;
		}
		iRegions++;
	}
}

void
config_set_access_key_id(const char *szInput)
{
	config_set(config.szAccessKeyId, szInput, 20);
}

void
config_set_secret_access_key(const char *szInput)
{
	config_set(config.szSecretAccessKey, szInput, 40);
}

void
config_set_token(const char *szInput)
{
	if (szInput == NULL) {
		return;
	}

	if (config.bufToken) {
		buffer_destroy(config.bufToken);
	}

	config.bufToken = buffer_from(szInput);
}

void
config_set_iam_role(__attribute__((unused)) const char *szInput)
{
	config.fIamRole = 1;
}

void
config_set_debug(__attribute__((unused)) const char *szInput)
{
	config.fDebug = 1;
}

void
config_load(int argc, char **argv)
{
	config_load_file("/etc/hawser");
	config_load_user_file();
	config_load_environment();
	config_load_arguments(argc, argv);

	if (config.fIamRole) {
		config_load_iam();
	}
}
