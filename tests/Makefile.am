## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I../include
AM_CFLAGS = -Wall -Wextra -std=c89 -pedantic -Werror @CHECK_CFLAGS@
LDADD = ../lib/libhawser.a @CHECK_LIBS@

# CHECK target
TESTS = lib_ec2_id lib_info_endpoints

check_PROGRAMS = $(TESTS)

lib_ec2_id_SOURCES = lib/ec2/id.c

lib_info_endpoints_SOURCES = lib/info/endpoints.c
