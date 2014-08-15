#include "strings.h"

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
