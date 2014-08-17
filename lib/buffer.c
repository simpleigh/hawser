#include <stdlib.h>
#include <string.h>

#include "buffer.h"

struct BUFFER {
	size_t cbBuffer;
	size_t cbContents;
	char *szBuffer;
};

static const size_t DEFAULT_BUFFER_SIZE = 1024;

BUFFER *
buffer_create(void)
{
	BUFFER *buffer = malloc(sizeof(BUFFER));
	if (!buffer) {
		exit(EXIT_FAILURE);
	}

	buffer->szBuffer = malloc(DEFAULT_BUFFER_SIZE);
	if (!buffer->szBuffer) {
		exit(EXIT_FAILURE);
	}

	buffer->cbBuffer = DEFAULT_BUFFER_SIZE;
	buffer->cbContents = 0;
	buffer->szBuffer[0] = '\0';

	return buffer;
}

BUFFER *
buffer_from(const char *szString)
{
	size_t cbString = strlen(szString);
	return buffer_nfrom(szString, cbString);
}

BUFFER *
buffer_nfrom(const char *szString, size_t cbString)
{
	BUFFER *buffer = malloc(sizeof(buffer));
	size_t cbBuffer;

	if (!buffer) {
		exit(EXIT_FAILURE);
	}

	cbBuffer = (cbString < DEFAULT_BUFFER_SIZE) ?
			DEFAULT_BUFFER_SIZE :
			cbString + 1;

	buffer->szBuffer = malloc(cbBuffer);
	if (!buffer->szBuffer) {
		exit(EXIT_FAILURE);
	}

	memcpy(buffer->szBuffer, szString, cbString);
	buffer->cbBuffer = cbBuffer;
	buffer->cbContents = cbString;
	buffer->szBuffer[cbString] = '\0';

	return buffer;
}

size_t
buffer_len(const BUFFER *buffer)
{
	if (!buffer) {
		exit(EXIT_FAILURE);
	}

	return buffer->cbContents;
}


const char *
buffer_data(const BUFFER *buffer)
{
	if (!buffer) {
		exit(EXIT_FAILURE);
	}

	return buffer->szBuffer;
}


size_t
buffer_append(BUFFER *buffer, const char *szString)
{
	size_t cbString = strlen(szString);
	return buffer_nappend(buffer, szString, cbString);
}


size_t
buffer_nappend(BUFFER *buffer, const char *szString, size_t cbString)
{
	if (!buffer || !buffer->szBuffer) {
		exit(EXIT_FAILURE);
	}

	if (buffer->cbBuffer - buffer->cbContents <= cbString) {
		/* TODO: cope with integer overflow here */
		size_t cbTarget = buffer->cbContents + cbString + 1;
		while (buffer->cbBuffer < cbTarget) {
			buffer->cbBuffer = buffer->cbBuffer * 2;
		}
		buffer->szBuffer = realloc(buffer->szBuffer, buffer->cbBuffer);
		if (!buffer->szBuffer) {
			exit(EXIT_FAILURE);
		}
	}

	memcpy(buffer->szBuffer + buffer->cbContents, szString, cbString);
	buffer->cbContents = buffer->cbContents + cbString;
	*(buffer->szBuffer + buffer->cbContents) = '\0';

	return buffer->cbContents;
}


size_t
buffer_append_line(BUFFER *buffer, const char *szString)
{
	size_t cbString = 0;

	if (!buffer || !buffer->szBuffer) {
		exit(EXIT_FAILURE);
	}

	while (szString[cbString] != '\0' && szString[cbString] != '\n') {
		cbString++;
	}

	return buffer_nappend(buffer, szString, cbString);
}


void
buffer_clear(BUFFER *buffer)
{
	if (!buffer || !buffer->szBuffer) {
		exit(EXIT_FAILURE);
	}

	buffer->cbContents = 0;
	buffer->szBuffer[0] = '\0';
}


void
buffer_destroy(BUFFER *buffer)
{
	if (!buffer) {
		return;
	}

	if (buffer->szBuffer) {
		free(buffer->szBuffer);
	}
	free(buffer);
}

