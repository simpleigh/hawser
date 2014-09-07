#include <stdio.h>
#include <stdlib.h>

#include "../lib/encodings.h"

int
main(int argc, char *argv[])
{
	BUFFER *buffer = buffer_create();

	if (argc < 2) {
		printf("Missing argument\n");
		exit(1);
	}

	encode_base16(buffer, argv[1]);
	puts(buffer_data(buffer));

	buffer_destroy(buffer);

	return 0;
}
