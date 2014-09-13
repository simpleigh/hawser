## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -Wall -Wextra -std=c89 -pedantic -Werror @CHECK_CFLAGS@
LDADD = $(top_builddir)/lib/libhawser.a @CHECK_LIBS@

# CHECK target
TESTS = ec2_id info_endpoints

check_PROGRAMS = $(TESTS)

ec2_id_SOURCES = ec2/id.c

info_endpoints_SOURCES = info/endpoints.c
