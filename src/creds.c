#include "../lib/credentials.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	credentials_load(argc, argv);
	printf("Access Key ID: %s\n",     credentials_get_access_key_id());
	printf("Secret access key: %s\n", credentials_get_secret_access_key());
	return 0;
}
