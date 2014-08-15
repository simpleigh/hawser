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


void
curl_get(BUFFER *buffer, const char *szUrl)
{
	if (!curl) {
		curl = curl_easy_init();
		if (!curl) {
			exit(EXIT_FAILURE);
		}
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
	}

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
	curl_easy_setopt(curl, CURLOPT_URL, szUrl);
	curl_easy_perform(curl);
}


void
curl_cleanup(void)
{
	if (curl) {
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
