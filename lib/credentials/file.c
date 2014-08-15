#include "../credentials.h"
#include "../buffer.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER 200

typedef struct FileEntry {
	const char * const name;
	const char * const pattern;
	regex_t *compiled;
	void (* const store)(const char *);
} FileEntry;

static FileEntry FILE_ENTRIES[] = {
	{
		"access_key_id",
		"[^ \t]{20}",
		NULL,
		credentials_set_access_key_id
	},
	{
		"secret_access_key",
		"[^ \t]{40}",
		NULL,
		credentials_set_secret_access_key
	},
	{
		NULL,
		NULL,
		NULL,
		NULL
	}
};

static void compile_regexes(FileEntry *fileEntry);
static void free_regexes(FileEntry *fileEntry);
static void free_regex(FileEntry *fileEntry);

void
credentials_load_file(const char *filename)
{
	FileEntry *fileEntry;
	FILE *stream = fopen(filename, "r");
	char szLine[LINE_BUFFER];

	printf("Loading %s\n", filename);

	if (!stream) {
		return;
	}

	compile_regexes(FILE_ENTRIES);

	while (fgets(szLine, LINE_BUFFER, stream)) {
		fileEntry = FILE_ENTRIES;
		while (fileEntry->name) {
			regmatch_t matchptr[2];
			if (fileEntry->compiled) {
				if (regexec(fileEntry->compiled, szLine, 2, matchptr, 0) == 0) {
					szLine[matchptr[1].rm_eo] = '\0';
					fileEntry->store(szLine + matchptr[1].rm_so);
				}
			}
			fileEntry++;
		}
	}

	free_regexes(FILE_ENTRIES);

	fclose(stream);
}

static void
compile_regexes(FileEntry *fileEntry)
{
	BUFFER *buffer;
	int result;

	while (fileEntry->name) {
		buffer = buffer_create();
		buffer_append(buffer, "^[ \t]*");
		buffer_append(buffer, fileEntry->name);
		buffer_append(buffer, "[ \t]*=[ \t]*(");
		buffer_append(buffer, fileEntry->pattern);
		buffer_append(buffer, ")[ \t]*");

		fileEntry->compiled = malloc(sizeof(regex_t));
		if (fileEntry->compiled) {
			result = regcomp(
				fileEntry->compiled,
				buffer_data(buffer),
				REG_EXTENDED
			);

			if (result) {
				free_regex(fileEntry);
			}
		}

		buffer_destroy(buffer);
		fileEntry++;
	}
}

static void
free_regexes(FileEntry *fileEntry)
{
	while (fileEntry->name) {
		if (fileEntry->compiled) {
			free_regex(fileEntry);
		}
		fileEntry++;
	}
}

static void
free_regex(FileEntry *fileEntry)
{
	regfree(fileEntry->compiled);
	free(fileEntry->compiled);
	fileEntry->compiled = NULL;
}

#undef LINE_BUFFER
