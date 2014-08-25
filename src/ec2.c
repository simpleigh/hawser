#include "../lib/config.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	config_load(argc, argv);
	printf("Instance: %s\n", config.szInstanceId);

	return 0;
}
