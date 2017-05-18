## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -std=c89 -Wall -Wextra -Werror -pedantic -pedantic-errors

# Main library
noinst_LIBRARIES = libhawser.a

libhawser_a_SOURCES = $(top_srcdir)/include/hawser/hawser.h \
                      $(top_srcdir)/include/hawser/ec2.h    \
                      $(top_srcdir)/include/hawser/info.h   \
                      $(top_srcdir)/include/hawser/lambda.h \
                      $(top_srcdir)/include/hawser/s3.h     \
                      $(top_srcdir)/include/hawser/sns.h    \
                      $(top_srcdir)/include/hawser/sqs.h    \
                      ec2/id.c          \
                      info/endpoints.c  \
                      info/regions.c    \
                      info/services.c   \
                      lambda/id.c       \
                      s3/id.c           \
                      sns/id.c          \
                      sqs/id.c          \
                      buffer.c          \
                      buffer.h          \
                      curl.c            \
                      curl.h            \
                      encodings.c       \
                      encodings.h       \
                      hawser_internal.h \
                      id.c              \
                      id.h              \
                      request.c         \
                      request.h
