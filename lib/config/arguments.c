#include <getopt.h>
#include <stdlib.h>

#include "../config.h"

const struct option GETOPT_OPTIONS[] = {
	{ "access-key-id",     required_argument, NULL, 0 },
	{ "secret-access-key", required_argument, NULL, 0 },
	{ "iam-role",          no_argument,       NULL, 0 },
	{ "debug",             no_argument,       NULL, 0 },
	{ NULL,                0,                 NULL, 0 }
};

/* Array of const pointers to functions. */
/* Should line up with GETOPT_OPTIONS. */
void (* const STORES[])(const char *) = {
	config_set_access_key_id,
	config_set_secret_access_key,
	config_set_iam_role,
	config_set_debug
};

void
config_load_arguments(int argc, char **argv)
{
	int c;

	while (1) {
		int iOption = -1;
		c = getopt_long(argc, argv, "", GETOPT_OPTIONS, &iOption);

		/* End of options. */
		if (c == -1) {
			break;
		}

		/* Matched long option. */
		if (c == 0 && iOption != -1) {
			STORES[iOption](optarg);
		}
	}
}
