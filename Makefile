CFLAGS = -g -O -Wall -Wextra -std=c89 -pedantic -Werror

.PHONY: build

build: credentials

credentials: credentials.c lib/credentials.c lib/credentials.h lib/credentials/arguments.c lib/credentials/file.c lib/credentials/environment.c lib/credentials/user-file.c lib/string.h lib/string.c
