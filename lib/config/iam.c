#include <stdio.h>

#include "../config.h"
#include "../buffer.h"
#include "../curl.h"

static const char * const URL_ROOT =
	"http://instance-data/latest/meta-data/iam/security-credentials/";

void
config_load_iam()
{
	BUFFER *bufResponse;
	BUFFER *bufUrl = buffer_from(URL_ROOT);

	bufResponse = buffer_create();
	if (!curl_get(bufResponse, URL_ROOT)) {
		goto err;
	}

	buffer_append_line(bufUrl, buffer_data(bufResponse));

	buffer_clear(bufResponse);
	if (!curl_get(bufResponse, buffer_data(bufUrl))) {
		goto err;
	}

	printf("%s\n", buffer_data(bufResponse));

err:
	buffer_destroy(bufResponse);
	buffer_destroy(bufUrl);
}
