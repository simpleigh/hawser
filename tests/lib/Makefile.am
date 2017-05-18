## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -std=c89 -Wall -Wextra -Werror -pedantic -pedantic-errors @CHECK_CFLAGS@
LDADD = $(top_builddir)/lib/libhawser.a @CHECK_LIBS@

# CHECK target
TESTS = test_ec2 test_info

check_PROGRAMS = $(TESTS)

test_ec2_SOURCES = ec2/id.c \
                   ec2.c    \
                   ec2.h

test_info_SOURCES = info/endpoints.c \
                    info/regions.c   \
                    info/services.c  \
                    info.c           \
                    info.h
