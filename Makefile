CFLAGS = -g -O -Wall -Wextra -std=c89 -pedantic -Werror

.PHONY: build

build: credentials

credentials: credentials.c lib/credentials.c lib/credentials.h lib/credentials/arguments.c lib/credentials/environment.c
