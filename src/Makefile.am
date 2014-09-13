## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -ansi -Werror -pedantic -Wall -Wextra
LDADD = $(top_builddir)/lib/libhawser.a

# Programs
bin_PROGRAMS = creds ec2 uriencode base16

creds_SOURCES = bin/creds.c          \
                config.h             \
                config.c             \
                config/arguments.c   \
                config/environment.c \
                config/file.c        \
                config/iam.c         \
                config/region.c      \
                config/user-file.c
creds_CPPFLAGS = @LIBCURL_CPPFLAGS@
creds_LDADD = $(LDADD) @LIBCURL@

ec2_SOURCES = bin/ec2.c
ec2_INCLUDES = @OPENSSL_INCLUDES@
ec2_LDFLAGS = @OPENSSL_LDFLAGS@
ec2_LDADD = $(LDADD) @OPENSSL_LIBS@

uriencode_SOURCES = bin/uriencode.c

base16_SOURCES = bin/base16.c
