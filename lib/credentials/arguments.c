#include "../credentials.h"

#include <getopt.h>
#include <stdlib.h>

const struct option GETOPT_OPTIONS[] = {
	{ "access-key-id",     required_argument, NULL, 0 },
	{ "secret-access-key", required_argument, NULL, 0 },
	{ NULL,                0,                 NULL, 0 }
};

/* Array of const pointers to functions. */
/* Should line up with GETOPT_OPTIONS. */
void (* const STORES[])(const char *) = {
	credentials_set_access_key_id,
	credentials_set_secret_access_key
};

void
credentials_load_arguments(int argc, char **argv)
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
