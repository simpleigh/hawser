#include "../lib/config.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	config_load(argc, argv);
	printf("Access Key ID: %s\n",     config.access_key_id);
	printf("Secret access key: %s\n", config.secret_access_key);
	return 0;
}
