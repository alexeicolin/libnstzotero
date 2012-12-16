# Copyright (C) 2012 Alexei Colin <alexei@alexeicolin.com>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

plugindir = $(libdir)/src

INCLUDES =					\
	-I$(top_builddir)			\
	-I$(top_srcdir)				\
	-DLOCALEDIR=\""$(datadir)/locale"\"	\
	$(NST_CFLAGS)				\
	$(WARN_CFLAGS)				\
	$(DISABLE_DEPRECATED)       \
	$(DEPS_CFLAGS)

plugin_LTLIBRARIES = libnstzotero.la

libnstzotero_la_SOURCES = nst-zotero.c
libnstzotero_la_LDFLAGS = -module -avoid-version
libnstzotero_la_LIBADD = $(NST_LIBS)

