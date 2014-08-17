#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "../config.h"
#include "../buffer.h"

#define LINE_BUFFER 200

typedef struct FileEntry {
	const char * const szParameter;
	const char * const szRegex;
	regex_t *pRegexCompiled;
	void (* const store)(const char *);
} FileEntry;

static FileEntry FILE_ENTRIES[] = {
	{
		"access_key_id",
		"[^ \t]{20}",
		NULL,
		config_set_access_key_id
	},
	{
		"secret_access_key",
		"[^ \t]{40}",
		NULL,
		config_set_secret_access_key
	},
	{
		NULL,
		NULL,
		NULL,
		NULL
	}
};

static void compile_regexes(FileEntry *pFileEntry);
static void free_regexes(FileEntry *pFileEntry);

void
config_load_file(const char *szFilename)
{
	FILE *pStream = fopen(szFilename, "r");
	char szLine[LINE_BUFFER];
	FileEntry *pFileEntry;
	int result;
	regmatch_t pMatches[2];

	printf("Loading %s\n", szFilename);

	if (!pStream) {
		return;
	}

	compile_regexes(FILE_ENTRIES);

	while (fgets(szLine, LINE_BUFFER, pStream)) {
		pFileEntry = FILE_ENTRIES;
		while (pFileEntry->szParameter) {
			result = regexec(
				pFileEntry->pRegexCompiled,            /* preg   */
				szLine,                                /* string */
				sizeof(pMatches) / sizeof(regmatch_t), /* nmatch */
				pMatches,                              /* pmatch */
				0                                      /* eflags */
			);

			if (result == 0) {
				/* Insert null at end of match. */
				szLine[pMatches[1].rm_eo] = '\0';
				pFileEntry->store(szLine + pMatches[1].rm_so);
			}

			pFileEntry++;
		}
	}

	free_regexes(FILE_ENTRIES);

	fclose(pStream);
}

static void
compile_regexes(FileEntry *fileEntry)
{
	BUFFER *bufRegex;
	int result;

	while (fileEntry->szParameter) {
		bufRegex = buffer_create();
		buffer_append(bufRegex, "^[ \t]*");
		buffer_append(bufRegex, fileEntry->szParameter);
		buffer_append(bufRegex, "[ \t]*=[ \t]*(");
		buffer_append(bufRegex, fileEntry->szRegex);
		buffer_append(bufRegex, ")[ \t]*");

		fileEntry->pRegexCompiled = malloc(sizeof(regex_t));
		if (!fileEntry->pRegexCompiled) {
			exit(EXIT_FAILURE);
		}

		result = regcomp(
			fileEntry->pRegexCompiled,
			buffer_data(bufRegex),
			REG_EXTENDED
		);
		if (result) {
			exit(EXIT_FAILURE);
		}

		buffer_destroy(bufRegex);
		fileEntry++;
	}
}

static void
free_regexes(FileEntry *fileEntry)
{
	while (fileEntry->szParameter) {
		if (fileEntry->pRegexCompiled) {
			regfree(fileEntry->pRegexCompiled);
			free(fileEntry->pRegexCompiled);
			fileEntry->pRegexCompiled = NULL;
		}
		fileEntry++;
	}
}

#undef LINE_BUFFER
