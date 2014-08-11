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
