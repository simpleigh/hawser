## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -std=c89 -Wall -Wextra -Werror -pedantic -pedantic-errors

# Main library
noinst_LIBRARIES = libhawser.a

libhawser_a_SOURCES = $(top_srcdir)/include/hawser/hawser.h         \
                      $(top_srcdir)/include/hawser/info.h           \
                      $(top_srcdir)/include/hawser/service/ec2.h    \
                      $(top_srcdir)/include/hawser/service/lambda.h \
                      $(top_srcdir)/include/hawser/service/s3.h     \
                      $(top_srcdir)/include/hawser/service/sns.h    \
                      $(top_srcdir)/include/hawser/service/sqs.h    \
                      info/endpoints.c    \
                      info/regions.c      \
                      info/services.c     \
                      service/ec2/id.c    \
                      service/lambda/id.c \
                      service/s3/id.c     \
                      service/sns/id.c    \
                      service/sqs/id.c    \
                      service/id.c        \
                      service/id.h        \
                      buffer.c            \
                      buffer.h            \
                      curl.c              \
                      curl.h              \
                      encodings.c         \
                      encodings.h         \
                      hawser_internal.h   \
                      request.c           \
                      request.h
