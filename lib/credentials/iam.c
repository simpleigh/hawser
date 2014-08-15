#include "../credentials.h"
#include "../strings.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

static const char const URL_ROOT[] =
	"http://instance-data/latest/meta-data/iam/security-credentials/";

size_t
credentials_read_rolename(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t bytes = size * nmemb;
	char **szData = (char **)userdata;

	*szData = malloc(bytes + 1);
	if (!*szData) {
		return 0;
	}

	memcpy(*szData, ptr, bytes);
	*szData[bytes] = '\0';

	return bytes;
}

void
credentials_load_iam()
{
	CURL *curl = curl_easy_init();
	char *szData;
	size_t cbUrl = 0;
	char *szUrl;

	if (!curl) {
		return;
	}

	curl_easy_setopt(curl, CURLOPT_URL, URL_ROOT);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, credentials_read_rolename);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szData);
	curl_easy_perform(curl);

	cbUrl = (sizeof(URL_ROOT) / sizeof(char)) + strlinelen(szData);
	szUrl = malloc(cbUrl);
	if (!szUrl) {
		return;
	}

	memcpy(szUrl, URL_ROOT, sizeof(URL_ROOT) / sizeof(char));
	memcpy(szUrl, szData, strlinelen(szData));
	szUrl[cbUrl] = '0';
	free(szData);

	curl_easy_setopt(curl, CURLOPT_URL, szUrl);

	curl_easy_cleanup(curl);
}
