#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([rectangle.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_FILES([Makefile])
LT_INIT()
AC_CONFIG_MACRO_DIR([m4])
PKG_CHECK_MODULES([SDL2], [sdl2])
PKG_CHECK_MODULES([SDL2_image], [SDL2_image])
PKG_CHECK_MODULES([SDL2_ttf], [SDL2_ttf])
PKG_CHECK_MODULES([OpenGL], [gl])

AM_CXXFLAGS="-std=c++11"
AC_SUBST([AM_CXXFLAGS])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.

AC_OUTPUT
