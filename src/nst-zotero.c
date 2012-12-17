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

#include <json-glib/json-glib.h>

/* TODO: move the URI to GNOME settings? */
#define ZOTERO_CONNECTOR_URI "http://127.0.0.1:23119/connector/"
#define ZOTERO_CONNECTOR_API_VERSION "2.1"

#define SAVE_ITEMS_STATUS_OK 201

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
    /* TODO: eventually, this could be a collection selector */
    GtkWidget *placeholder_widget = gtk_label_new ("");
    return placeholder_widget;
}

static gchar *
build_save_items_request (GList *file_list)
{
    GList *l;

    JsonBuilder *json_builder = json_builder_new ();
    json_builder_begin_object (json_builder);

    json_builder_set_member_name (json_builder, "items");
    json_builder_begin_array (json_builder);
    for (l = file_list; l; l = l->next) {
        gchar *path = l->data;

        json_builder_begin_object (json_builder);
        json_builder_set_member_name (json_builder, "itemType");
        json_builder_add_string_value (json_builder, "attachment");
        json_builder_set_member_name (json_builder, "path");
        json_builder_add_string_value (json_builder, path);
        json_builder_end_object (json_builder);
    }
    json_builder_end_array (json_builder);

    json_builder_set_member_name (json_builder, "attachmentMode");
    json_builder_add_string_value (json_builder, "file");
    json_builder_end_object (json_builder);

    JsonGenerator *json_gen = json_generator_new ();
    JsonNode *root = json_builder_get_root (json_builder);
    json_generator_set_root (json_gen, root);
    gchar *save_items_request = json_generator_to_data (json_gen, NULL);
    json_node_free (root);
    g_object_unref (json_gen);
    g_object_unref (json_builder);
    return save_items_request;
}

static gboolean
send_files (NstPlugin *plugin,
            GtkWidget *contact_widget,
            GList *file_list)
{
    if (!file_list)
        return TRUE; /* returning false, just hangs the send-to dialog */

    gchar *save_items_req = build_save_items_request (file_list);

    SoupSession *soup_session = soup_session_sync_new ();
    SoupMessage *save_msg =
        soup_message_new ("POST", ZOTERO_CONNECTOR_URI"saveItems");
    soup_message_set_request (save_msg, "application/json", SOUP_MEMORY_TAKE,
            save_items_req, strlen (save_items_req));
    soup_message_headers_append (save_msg->request_headers,
            "X-Zotero-Connector-API-Version", ZOTERO_CONNECTOR_API_VERSION);

    guint status = soup_session_send_message(soup_session, save_msg);
    if (status != SAVE_ITEMS_STATUS_OK)
        g_warning ("nst-zotero: send failed: response to saveItems: %u\n", status);
    /* TODO: returning false just hands the send-to dialog, how to fail? */
    g_object_unref (save_msg);
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
    NULL,
    send_files,
    destroy
};

NST_INIT_PLUGIN (plugin_info)
