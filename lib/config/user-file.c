#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#include "../config.h"
#include "../buffer.h"

void
config_load_user_file()
{
	struct passwd *pPasswd = getpwuid(getuid());
	BUFFER *bufFilename;

	if (!pPasswd || !pPasswd->pw_dir) {
		return;
	}

	bufFilename = buffer_from(pPasswd->pw_dir);
	buffer_append(bufFilename, "/.hawser");
	config_load_file(buffer_data(bufFilename));
	buffer_destroy(bufFilename);
}
