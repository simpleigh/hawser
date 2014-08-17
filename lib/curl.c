#include <curl/curl.h>
#include <stdlib.h>

#include "curl.h"
#include "buffer.h"

static CURL *curl = NULL;


static size_t
curl_write(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t bytes = size * nmemb;
	BUFFER *buffer = (BUFFER *)userdata;

	buffer_nappend(buffer, ptr, bytes);

	return bytes;
}


unsigned int
curl_get(BUFFER *buffer, const char *szUrl)
{
	CURLcode result;
	long responseCode;

	if (!curl) {
		curl = curl_easy_init();
		if (!curl) {
			exit(EXIT_FAILURE);
		}
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
	}

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
	curl_easy_setopt(curl, CURLOPT_URL, szUrl);
	result = curl_easy_perform(curl);
	if (result != CURLE_OK) {
		return 0;
	}

	result = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
	if (result != CURLE_OK) {
		return 0;
	}

	if (responseCode != 200) {
		return 0;
	}

	return 1;
}


void
curl_cleanup(void)
{
	if (curl) {
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
