## Process this file with automake to produce Makefile.in

# Global configuration
AM_CPPFLAGS = -I../include
AM_CFLAGS = -Wall -Wextra -std=c89 -pedantic -Werror

# Main library
noinst_LIBRARIES = libhawser.a

libhawser_a_SOURCES = ../include/hawser/hawser.h \
                      ../include/hawser/ec2.h    \
                      buffer.h                   \
                      buffer.c                   \
                      curl.h                     \
                      curl.c                     \
                      ec2/resourceId.c           \
                      encodings.h                \
                      encodings.c
