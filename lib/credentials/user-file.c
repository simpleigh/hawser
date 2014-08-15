#include "../credentials.h"
#include "../buffer.h"

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
	BUFFER *buffer;

	if (!pw || !pw->pw_dir) {
		return;
	}

	buffer = buffer_from(pw->pw_dir);
	buffer_append(buffer, "/.hawser");
	credentials_load_file(buffer_data(buffer));
	buffer_destroy(buffer);
}
