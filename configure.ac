# Copyright (C) 2012 Alexei Colin <alexei@alexeicolin.com>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([libnstzotero],
        [0.0.1],
        [Alexei Colin alexei@alexeicolin.com],
        [libnstzotero])
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])
AC_CONFIG_MACRO_DIR([m4])

LF_CONFIGURE_CC
LF_HOST_TYPE
LF_SET_WARNINGS

# Check for programs
AM_PATH_GLIB_2_0

# Initialize libtool
LT_PREREQ([2.2])
LT_INIT([disable-static])

AC_CONFIG_FILES([
   Makefile
   doc/Makefile
   m4/Makefile
   src/Makefile
   po/Makefile.in
])

# -----------------------------------------------------------
# Language Support
# -----------------------------------------------------------
IT_PROG_INTLTOOL([0.40.0])

GETTEXT_PACKAGE=libnstzotero
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE",[Gettext package name])
AM_GLIB_GNU_GETTEXT

# -----------------------------------------------------------
# Pkg-Config dependency checks
# -----------------------------------------------------------

NAUTILUS_SENDTO_REQUIRED=3.0.1

AC_CHECK_LIBM
AC_SUBST(LIBM)

PKG_CHECK_MODULES(DEPS,
[
   glib-2.0
   gmodule-export-2.0
   gobject-2.0
   nautilus-sendto >= $NAUTILUS_SENDTO_REQUIRED
   json-glib-1.0
   libsoup-2.4
])

AC_OUTPUT
