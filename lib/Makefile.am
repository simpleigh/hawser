ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I../include

AM_CFLAGS = -Wall -Wextra -std=c89 -pedantic -Werror

noinst_LIBRARIES = libhawser.a

libhawser_a_SOURCES = ../include/hawser/hawser.h \
                      buffer.h                   \
                      buffer.c                   \
                      curl.h                     \
                      curl.c                     \
                      ec2/resourceId.c           \
                      encodings.h                \
                      encodings.c
