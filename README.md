Welcome to libnstzotero.

This is a plugin for GNOME's nautilus-sendto application that allows you to add
files into Zotero. The primary use case is to add PDFs from evince directly to
Zotero (without having to Alt-TAB into Zotero).

Currently, this requires a patched Zotero. A flag needs to be exposed in the
connector interface. The patch is in zotero/ directory. The plan is to ask
upstream to include the patch, and if not, then make a Zotero extension that
extends the connector with a dedicated end-point.
UPDATE: The patch has security implications since websites have access to the
connector (see the [pull request](https://github.com/zotero/zotero/pull/212)).

libnstzotero is free software. Please see the file COPYING for details.
For documentation, please see the files in the doc subdirectory.
For building and installation instructions please see the INSTALL file.
