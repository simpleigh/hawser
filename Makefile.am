## Process this file with automake to produce Makefile.in

# Global configuration
AM_CFLAGS = -g -O -Wall -Wextra -std=c89 -pedantic -Werror

# Binary
bin_PROGRAMS = creds

creds_SOURCES = src/creds.c                   \
                lib/credentials.h             \
                lib/credentials.c             \
                lib/credentials/arguments.c   \
                lib/credentials/environment.c \
                lib/credentials/file.c        \
                lib/credentials/user-file.c   \
                lib/string.h                  \
                lib/string.c
