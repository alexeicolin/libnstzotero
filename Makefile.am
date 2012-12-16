# Copyright (C) 2012 Alexei Colin <alexei@alexeicolin.com>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

INTLTOOL_FILES = intltool-extract.in \
				 intltool-merge.in \
				 intltool-update.in

EXTRA_DIST = reconf configure $(INTLTOOL_FILES)
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = m4 src doc po

DISTCLEANFILES = ... intltool-extract \
				 intltool-merge \
				 intltool-update \
				 po/.intltool-merge-cache
