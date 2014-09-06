#include <stdlib.h>
#include <string.h>

#include "buffer.h"

struct buffer {
	size_t cbBuffer;
	size_t cbContents;
	char *szBuffer;
	char *szContents;
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
	buffer->szContents = buffer->szBuffer;
	buffer->szContents[buffer->cbContents] = '\0';

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
	BUFFER *buffer = malloc(sizeof(BUFFER));
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

	buffer->cbBuffer = cbBuffer;
	buffer->cbContents = cbString;
	buffer->szContents = buffer->szBuffer;
	buffer->szContents[cbString] = '\0';
	memcpy(buffer->szContents, szString, cbString);

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

	return buffer->szContents;
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
	size_t dContents;

	if (!buffer || !buffer->szBuffer) {
		exit(EXIT_FAILURE);
	}

	dContents = buffer->szContents - buffer->szBuffer;

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
		buffer->szContents = buffer->szBuffer + dContents;
	}

	memcpy(buffer->szContents + buffer->cbContents, szString, cbString);
	buffer->cbContents = buffer->cbContents + cbString;
	*(buffer->szContents + buffer->cbContents) = '\0';

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
	buffer->szContents = buffer->szBuffer;
	buffer->szContents[buffer->cbContents] = '\0';
}


size_t
buffer_substr(BUFFER *buffer, int ibStart, int cbLength)
{
	if (!buffer || !buffer->szBuffer) {
		exit(EXIT_FAILURE);
	}

	if (ibStart < 0 && (size_t)(-ibStart) < buffer->cbContents) {
		ibStart = buffer->cbContents + ibStart;
	}

	if (ibStart > 0 && (size_t)ibStart < buffer->cbContents) {
		buffer->cbContents = buffer->cbContents - ibStart;
		buffer->szContents = buffer->szContents + ibStart;
	}

	if (cbLength < 0 && (size_t)(-cbLength) < buffer->cbContents) {
		cbLength = buffer->cbContents + cbLength;
	}

	if (cbLength > 0 && (size_t)cbLength < buffer->cbContents) {
		buffer->cbContents = cbLength;
		buffer->szContents[buffer->cbContents] = '\0';
	}

	return buffer->cbContents;
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
