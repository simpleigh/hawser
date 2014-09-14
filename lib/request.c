#include <stdlib.h>

#include "buffer.h"

#include "request.h"


struct request {
	BUFFER *hostname;
	BUFFER *path;
};


REQUEST *
request_create(const char *hostname, const char *path)
{
	REQUEST *request = malloc(sizeof(REQUEST));

	if (!request) {
		exit(EXIT_FAILURE);
	}

	request->hostname = buffer_from(hostname);
	request->path     = buffer_from(path);

	return request;
}


void
request_destroy(REQUEST *request)
{
	if (!request) {
		return;
	}

	free(request);
}
