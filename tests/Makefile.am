## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I../include
AM_CFLAGS = -Wall -Wextra -std=c89 -pedantic -Werror @CHECK_CFLAGS@
LDADD = ../lib/libhawser.a @CHECK_LIBS@

# CHECK target
TESTS = test_lib_ec2_resourceId

check_PROGRAMS = $(TESTS)

test_lib_ec2_resourceId_SOURCES = lib/ec2/resourceId.c
