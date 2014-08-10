#include "../credentials.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct FileEntry {
	const char * const regex;
	regex_t *compiled;
	void (* const store)(const char *);
} FileEntry;

static FileEntry FILE_ENTRIES[] = {
	{
		"^[ \t]*access_key_id[ \t]*=[ \t]*([^ \t]{20})[ \t]*",
		NULL,
		credentials_set_access_key_id
	},
	{
		"^[ \t]*secret_access_key[ \t]*=[ \t]*([^ \t]{40})[ \t]*",
		NULL,
		credentials_set_secret_access_key
	},
	{
		NULL,
		NULL,
		NULL
	}
};

#define LINE_BUFFER 80

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

	fileEntry = FILE_ENTRIES;
	while (fileEntry->regex) {
		fileEntry->compiled = malloc(sizeof(regex_t));
		if (fileEntry->compiled) {
			regcomp(fileEntry->compiled, fileEntry->regex, REG_EXTENDED);
		}
		fileEntry++;
	}

	while (fgets(szLine, LINE_BUFFER, stream)) {
		fileEntry = FILE_ENTRIES;
		while (fileEntry->regex) {
			regmatch_t matchptr[2];
			int result = regexec(fileEntry->compiled, szLine, 2, matchptr, 0);
			if (result == 0) {
				szLine[matchptr[1].rm_eo] = '\0';
				fileEntry->store(szLine + matchptr[1].rm_so);
			}
			fileEntry++;
		}
	}

	fileEntry = FILE_ENTRIES;
	while (fileEntry->regex) {
		regfree(fileEntry->compiled);
		fileEntry++;
	}

	fclose(stream);
}
