#include "../credentials.h"

#include <getopt.h>
#include <stdlib.h>

const struct option OPTIONS[] = {
	{ "access-key-id",     required_argument, NULL, 0 },
	{ "secret-access-key", required_argument, NULL, 0 },
	{ NULL,                0,                 NULL, 0 }
};

typedef struct Option {
	void (*store)(char *);
} Option;

const Option OPTS[] = {
	{ credentials_set_access_key_id     },
	{ credentials_set_secret_access_key }
};

void
credentials_load_arguments(int argc, char **argv)
{
	int c;

	while (1) {
		int option_index = 0;
		c = getopt_long(argc, argv, "", OPTIONS, &option_index);
		if (c == -1) {
			break;
		}

		OPTS[option_index].store(optarg);
	}
}
