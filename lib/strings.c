#include "strings.h"

char *
strappend(char *szDestination, const char *szSource)
{
	while (*szSource) {
		*szDestination = *szSource;
		szDestination++;
		szSource++;
	}

	return szDestination;
}

size_t
strlinelen(const char *szString)
{
	size_t cbString = 0;

	while (*szString != '\0' && *szString != '\n') {
		szString++;
		cbString++;
	}

	return cbString;
}
