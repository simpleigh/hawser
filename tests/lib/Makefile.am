## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -std=c89 -Wall -Wextra -Werror -pedantic -pedantic-errors @CHECK_CFLAGS@
LDADD = $(top_builddir)/lib/libhawser.a @CHECK_LIBS@

# CHECK target
TESTS = test

check_PROGRAMS = $(TESTS)

test_SOURCES = info/endpoints.c    \
               info/regions.c      \
               info/services.c     \
               service/ec2/id.c    \
               service/lambda/id.c \
               service/s3/id.c     \
               service/sns/id.c    \
               service/sqs/id.c    \
               service/ec2.c       \
               service/ec2.h       \
               service/lambda.c    \
               service/lambda.h    \
               service/s3.c        \
               service/s3.h        \
               service/sns.c       \
               service/sns.h       \
               service/sqs.c       \
               service/sqs.h       \
               info.c              \
               info.h              \
               test.c
