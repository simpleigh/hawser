#include <stdio.h>

#include "../config.h"
#include "../buffer.h"
#include "../curl.h"

static const char * const URL =
	"http://instance-data/latest/meta-data/placement/availability-zone";

void
config_load_region(void)
{
	BUFFER *bufResponse = buffer_create();

	if (!curl_get(bufResponse, URL)) {
		buffer_destroy(bufResponse);
		return;
	}

	printf("%s", buffer_data(bufResponse));
}
