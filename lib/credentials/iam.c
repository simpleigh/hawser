#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#include "../credentials.h"
#include "../buffer.h"

static const char const URL_ROOT[] =
	"http://instance-data/latest/meta-data/iam/security-credentials/";

size_t
curl_read(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t bytes = size * nmemb;
	BUFFER *buffer = (BUFFER *)userdata;

	buffer_nappend(buffer, ptr, bytes);

	return bytes;
}

void
credentials_load_iam()
{
	CURL *curl = curl_easy_init();
	BUFFER *response;
	BUFFER *url = buffer_from(URL_ROOT);

	if (!curl) {
		return;
	}

	response = buffer_create();
	curl_easy_setopt(curl, CURLOPT_URL, URL_ROOT);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_read);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
	curl_easy_perform(curl);

	buffer_append(url, "/");
	buffer_nappend(
		url,
		buffer_data(response),
		strlinelen(buffer_data(response))
	);

	buffer_clear(response);
	curl_easy_setopt(curl, CURLOPT_URL, buffer_data(url));
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_read);
	curl_easy_perform(curl);

	printf("%s\n", buffer_data(response));

	buffer_destroy(response);
	buffer_destroy(url);
	curl_easy_cleanup(curl);
}
