#include "../lib/config.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	config_load(argc, argv);
	printf("Access Key ID: %s\n",     config.szAccessKeyId);
	printf("Secret access key: %s\n", config.szSecretAccessKey);
	return 0;
}
