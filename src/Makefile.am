AM_CFLAGS = -Wall -Wextra -std=c89 -pedantic -Werror

LDADD = ../lib/libhawser.a @LIBCURL@

AC_CPPFLAGS = @LIBCURL_CPPFLAGS@

bin_PROGRAMS = creds ec2 uriencode base16

creds_SOURCES = bin/creds.c

ec2_SOURCES = bin/ec2.c
ec2_LDADD = ../lib/libhawser.a @OPENSSL_LDFLAGS@ @OPENSSL_LIBS@ @LIBCURL@
ec2_INCLUDES = @OPENSSL_INCLUDES@

uriencode_SOURCES = bin/uriencode.c
uriencode_LDADD = ../lib/libhawser.a

base16_SOURCES = bin/base16.c
base16_LDADD = ../lib/libhawser.a
