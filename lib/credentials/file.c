#include "../credentials.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

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

static void
strappend(char **pszDestination, const char *szSource)
{
	while (*szSource) {
		**pszDestination = *szSource;
		(*pszDestination)++;
		szSource++;
	}
}

static void
free_regex(FileEntry *fileEntry)
{
	regfree(fileEntry->compiled);
	free(fileEntry->compiled);
	fileEntry->compiled = NULL;
}

#define REGEX_BUFFER 80

static void
compile_regexes(FileEntry *fileEntry)
{
	char szRegex[REGEX_BUFFER];
	char *szPointer;
	int result;

	while (fileEntry->name) {
		szPointer = szRegex;
		strappend(&szPointer, "^[ \t]*");
		strappend(&szPointer, fileEntry->name);
		strappend(&szPointer, "[ \t]*=[ \t]*(");
		strappend(&szPointer, fileEntry->pattern);
		strappend(&szPointer, ")[ \t]*");
		*szPointer = '\0';

		fileEntry->compiled = malloc(sizeof(regex_t));
		if (fileEntry->compiled) {
			result = regcomp(fileEntry->compiled, szRegex, REG_EXTENDED);
			if (result) {
				free_regex(fileEntry);
			}
		}

		fileEntry++;
	}
}

#undef REGEX_BUFFER

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

#define LINE_BUFFER 200

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

#undef LINE_BUFFER
