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

#ifdef HAVE_GNOME
#include <libsoup/soup-gnome.h>
#else
#include <libsoup/soup.h>
#endif

/* TODO: move the URI to GNOME settings */
#define ZOTERO_CONNECTOR_URI "http://127.0.0.1:23119/connector/ping"
#define ZOTERO_CONNECTOR_API_VERSION "2"
#define ZOTERO_VERSION "3.0.11.1"

#define HTTP_STATUS_OK 200

static gboolean
init(NstPlugin *plugin)
{
    g_print ("Init %s plugin\n", plugin->info->id);
    return TRUE;
}

static gboolean
destroy(NstPlugin *plugin)
{
    g_print ("Destroy %s plugin\n", plugin->info->id);
    return TRUE;
}

static GtkWidget *
get_contacts_widget(NstPlugin *plugin)
{
    GtkWidget *placeholder_widget = gtk_label_new ("");
    return placeholder_widget;
}

static gboolean
validate_destination (NstPlugin *plugin,
        GtkWidget *contact_widget,
        gchar **error)
{
    g_print ("nst-zotero: destination valid\n");
    return TRUE;
}

static gboolean
send_files (NstPlugin *plugin,
            GtkWidget *contact_widget,
            GList *file_list)
{
    guint status;
    SoupSession *soup_session = soup_session_sync_new ();
    SoupMessage *ping_msg = soup_message_new ("POST", ZOTERO_CONNECTOR_URI);
    soup_message_headers_append (ping_msg->request_headers,
            "Content-Type", "application/json");
    soup_message_headers_append (ping_msg->request_headers,
            "X-Zotero-Version", ZOTERO_VERSION);
    soup_message_headers_append (ping_msg->request_headers,
            "X-Zotero-Connector-API-Version", ZOTERO_CONNECTOR_API_VERSION);
    g_print ("nst-zotero: send files\n");
    status = soup_session_send_message(soup_session, ping_msg);
    g_print ("nst-zotero: response status %u\n", status);
    if (status != HTTP_STATUS_OK)
        g_warning ("nst-zotero: send failed: response status %u\n", status);
    g_object_unref (ping_msg);
    g_object_unref (soup_session);
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
