## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -std=c89 -Wall -Wextra -Werror -pedantic -pedantic-errors

# Main library
noinst_LIBRARIES = libhawser.a

libhawser_a_SOURCES = $(top_srcdir)/include/hawser/hawser.h \
                      $(top_srcdir)/include/hawser/ec2.h    \
                      $(top_srcdir)/include/hawser/info.h   \
                      ec2/id.c          \
                      info/endpoints.c  \
                      info/regions.c    \
                      info/services.c   \
                      buffer.c          \
                      buffer.h          \
                      curl.c            \
                      curl.h            \
                      encodings.c       \
                      encodings.h       \
                      hawser_internal.h \
                      request.c         \
                      request.h
