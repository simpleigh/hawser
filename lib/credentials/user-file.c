#include "../credentials.h"

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

void
credentials_load_user_file()
{
	uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	size_t cbHomeDirectory;
	char *szFilename;

	if (!pw || !pw->pw_dir) {
		return;
	}

	cbHomeDirectory = strlen(pw->pw_dir);
	szFilename = malloc(
		cbHomeDirectory
			+ 8 /* '/' '.' 'h' 'a' 'w' 's' 'e' 'r' */
			+ 1 /* Terminating null. */
	);

	if (!szFilename) {
		return;
	}

	strncpy(szFilename, pw->pw_dir, cbHomeDirectory);
	strcpy(szFilename + cbHomeDirectory, "/.hawser");

	credentials_load_file(szFilename);
	free(szFilename);
}
