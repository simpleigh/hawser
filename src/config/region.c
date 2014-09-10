#include <stdio.h>

#include "../config.h"
#include "../../lib/buffer.h"
#include "../../lib/curl.h"

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

	buffer_substr(bufResponse, 0, -1);

	config_set_region(buffer_data(bufResponse));

	buffer_destroy(bufResponse);
}
