#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "../../lib/buffer.h"
#include "../../lib/curl.h"

static const char * const URL_ROOT =
	"http://instance-data/latest/meta-data/iam/security-credentials/";

typedef struct IamCredentials {
	BUFFER *bufCode;
	BUFFER *bufAccessKeyId;
	BUFFER *bufSecretAccessKey;
	BUFFER *bufToken;
} IamCredentials;

static IamCredentials credentials = { NULL, NULL, NULL, NULL };

typedef struct IamEntry {
	const char * const szName;
	const char * const szRegex;
	BUFFER **pszValue;
} IamEntry;

static const IamEntry IAM_ENTRIES[] = {
	{ "Code",            "[A-Za-z]+",         &credentials.bufCode            },
	{ "AccessKeyId",     "[A-Z0-9]{20}",      &credentials.bufAccessKeyId     },
	{ "SecretAccessKey", "[A-Za-z0-9+/]{40}", &credentials.bufSecretAccessKey },
	{ "Token",           "[A-Za-z0-9+/=]+",   &credentials.bufToken           },
	{ NULL,              NULL,                NULL                            }
};

static void process_entry(const IamEntry *pIamEntry, BUFFER *bufResponse);
static void check_and_save_credentials(void);

void
config_load_iam()
{
	BUFFER *bufResponse;
	BUFFER *bufUrl = buffer_from(URL_ROOT);
	const IamEntry *pIamEntry = IAM_ENTRIES;

	bufResponse = buffer_create();
	if (!curl_get(bufResponse, URL_ROOT)) {
		goto err;
	}

	buffer_append_line(bufUrl, buffer_data(bufResponse));

	buffer_clear(bufResponse);
	if (!curl_get(bufResponse, buffer_data(bufUrl))) {
		goto err;
	}

	while (pIamEntry->szName) {
		process_entry(pIamEntry, bufResponse);
		pIamEntry++;
	}

	check_and_save_credentials();

	buffer_destroy(credentials.bufCode);
	buffer_destroy(credentials.bufAccessKeyId);
	buffer_destroy(credentials.bufSecretAccessKey);
	buffer_destroy(credentials.bufToken);

err:
	buffer_destroy(bufResponse);
	buffer_destroy(bufUrl);
}

static void
process_entry(const IamEntry *pIamEntry, BUFFER *bufResponse)
{
	BUFFER *bufRegex;
	regex_t *pRegexCompiled;
	int result;
	regmatch_t rgMatches[2];

	bufRegex = buffer_create();
	buffer_append(bufRegex, "\"");
	buffer_append(bufRegex, pIamEntry->szName);
	buffer_append(bufRegex, "\" : \"(");
	buffer_append(bufRegex, pIamEntry->szRegex);
	buffer_append(bufRegex, ")\"");

	pRegexCompiled = malloc(sizeof(regex_t));
	if (!pRegexCompiled) {
		exit(EXIT_FAILURE);
	}

	result = regcomp(
		pRegexCompiled,
		buffer_data(bufRegex),
		REG_EXTENDED
	);
	if (result) {
		exit(EXIT_FAILURE);
	}

	buffer_destroy(bufRegex);

	result = regexec(
		pRegexCompiled,           /* preg   */
		buffer_data(bufResponse), /* string */
		2,                        /* nmatch */
		rgMatches,                /* pmatch */
		0                         /* eflags */
	);

	if (result == 0) {
		*(pIamEntry->pszValue) = buffer_nfrom(
			buffer_data(bufResponse) + rgMatches[1].rm_so,
			rgMatches[1].rm_eo - rgMatches[1].rm_so
		);
	}

	regfree(pRegexCompiled);
	free(pRegexCompiled);
}

void
check_and_save_credentials(void)
{
	if (credentials.bufCode
		&& credentials.bufAccessKeyId
		&& credentials.bufSecretAccessKey
		&& credentials.bufToken
		&& strcmp(buffer_data(credentials.bufCode), "Success") == 0
	) {
		config_set_access_key_id(buffer_data(credentials.bufAccessKeyId));
		config_set_secret_access_key(
			buffer_data(credentials.bufSecretAccessKey)
		);
		config_set_token(buffer_data(credentials.bufToken));
	}
}
