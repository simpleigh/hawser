#include <stdio.h>

#include "../credentials.h"
#include "../buffer.h"
#include "../curl.h"

static const char const URL_ROOT[] =
	"http://instance-data/latest/meta-data/iam/security-credentials/";

void
credentials_load_iam()
{
	BUFFER *response;
	BUFFER *url = buffer_from(URL_ROOT);

	response = buffer_create();
	curl_get(response, URL_ROOT);

	buffer_append_line(url, buffer_data(response));

	buffer_clear(response);
	curl_get(response, buffer_data(url));

	printf("%s\n", buffer_data(response));

	buffer_destroy(response);
	buffer_destroy(url);
}
