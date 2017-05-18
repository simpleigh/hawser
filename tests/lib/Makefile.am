## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -std=c89 -Wall -Wextra -Werror -pedantic -pedantic-errors @CHECK_CFLAGS@
LDADD = $(top_builddir)/lib/libhawser.a @CHECK_LIBS@

# CHECK target
TESTS = test

check_PROGRAMS = $(TESTS)

test_SOURCES = ec2/id.c         \
               info/endpoints.c \
               info/regions.c   \
               info/services.c  \
               ec2.c            \
               ec2.h            \
               info.c           \
               info.h           \
               test.c
