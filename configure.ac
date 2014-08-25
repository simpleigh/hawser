## Process this file with autoconf to produce a configure script.

AC_INIT([hawser], [0.1])
AC_CONFIG_SRCDIR([src/creds.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR
AM_PROG_CC_C_O

# Checks for libraries.
LIBCURL_CHECK_CONFIG(
	[yes],
	[7.10.8],
	[],
	[AC_MSG_ERROR([Cannot find libcurl: aborting.])]
)

# Output files.
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile lib/Makefile src/Makefile])

AC_OUTPUT
