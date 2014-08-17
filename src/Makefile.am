AM_CFLAGS = -Wall -Wextra -std=c89 -pedantic -Werror

LDADD = ../lib/libhawser.a @LIBCURL@

AC_CPPFLAGS = @LIBCURL_CPPFLAGS@

bin_PROGRAMS = creds

creds_SOURCES = creds.c
