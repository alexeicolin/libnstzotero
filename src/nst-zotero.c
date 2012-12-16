/*
 * Copyright (C) 2012 Alexei Colin <alexei@alexeicolin.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more av.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301  USA.
 *
 * Authors: Alexei Colin <alexei@alexeicolin.com>
 */

#include "config.h"

#include <glib.h>
#include <glib/gi18n-lib.h>
#include <nautilus-sendto-plugin.h>

static gboolean
init(NstPlugin *plugin)
{
    g_print("Init %s plugin\n", plugin->info->id);
    return TRUE;
}

static gboolean
destroy(NstPlugin *plugin)
{
    g_print("Destroy %s plugin\n", plugin->info->id);
    return TRUE;
}

static GtkWidget *
get_contacts_widget(NstPlugin *plugin)
{
    GtkWidget *placeholder_widget = gtk_label_new("");
    return placeholder_widget;
}

static gboolean
validate_destination (NstPlugin *plugin,
        GtkWidget *contact_widget,
        gchar **error)
{
    g_print("nst-zotero: destination valid\n");
    return TRUE;
}

static gboolean
send_files (NstPlugin *plugin,
            GtkWidget *contact_widget,
            GList *file_list)
{
    g_print("nst-zotero: send files\n");
    return TRUE;
}


static
NstPluginInfo plugin_info = {
    "zotero",
    "zotero",
    N_("Add to Zotero"),
    GETTEXT_PACKAGE,
    NAUTILUS_CAPS_NONE,
    init,
    get_contacts_widget,
    validate_destination,
    send_files,
    destroy
};

NST_INIT_PLUGIN (plugin_info)
