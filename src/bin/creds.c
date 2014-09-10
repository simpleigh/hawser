#include "../lib/buffer.h"
#include "../lib/config.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	config_load(argc, argv);
	printf("Region: %s\n",            config.szRegion);
	printf("Access Key ID: %s\n",     config.szAccessKeyId);
	printf("Secret access key: %s\n", config.szSecretAccessKey);
	if (config.bufToken) {
		printf("Token: %s\n", buffer_data(config.bufToken));
	}
	return 0;
}
