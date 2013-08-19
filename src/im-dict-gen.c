/* vim:set et sts=4: */
/* im-dict-ja - Japanese word dictionary set for input method.
 * Copyright (C) 2010-2011 Takao Fujiwara <takao.fujiwara1@gmail.com>
 * Copyright (C) 2010-2011 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.     See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>
#include "xml-parse.h"

static gchar *xml_file;

static const GOptionEntry entries[] =
{
  { "xml", 'x', 0, G_OPTION_ARG_STRING, &xml_file, "XML_FILE defines the dictionary format of PARSED_FILE", NULL },
  { NULL },
};

static gchar *
get_contents (const gchar *file)
{
    gchar *contents = NULL;
    gsize length;
    GError *error = NULL;

    if (!g_file_test (file, G_FILE_TEST_EXISTS)) {
        g_printerr ("%s does not exist\n", file);
        return NULL;
    }

    if (!g_file_get_contents (file, &contents, &length, &error)) {
        g_printerr ("Reading %s: %s\n", file, error->message);
        g_error_free (error);
        return NULL;
    }
    return contents;
}

static gchar *
convert_line (const gchar *line, GHashTable *hash)
{
    GString *string = NULL;
    const gchar *format;
    const gchar *replace_from;
    const gchar *replace_to;
    gchar **lines = NULL;
    gchar **formats = NULL;
    gchar *new_line = NULL;
    int i, j;

    if (line[0] == '#') {
        return g_strdup (line);
    }
    string = g_string_new (NULL);
    format = (const gchar *) g_hash_table_lookup (hash, (gpointer) "format");
    replace_from = (const gchar *) g_hash_table_lookup (hash, (gpointer) "replace_from");
    replace_to = (const gchar *) g_hash_table_lookup (hash, (gpointer) "replace_to");
    lines = g_strsplit (line, " ", -1);
    formats = g_strsplit (format, " ", -1);
    for (i = 0; i < g_strv_length (formats); i++) {
        if (i != 0) {
            string = g_string_append (string, " ");
        }
        if (strlen (formats[i]) == 1) {
            string = g_string_append (string, formats[i]);
        }
        else if (formats[i][0] == '$') {
            if (formats[i][1] == '$') {
                string = g_string_append (string, "$");
            } else {
                j = g_ascii_strtoll (formats[i] + 1, NULL, 0);
                if (j > g_strv_length (lines) || j <= 0) {
                    continue;
                }
                if (lines[j - 1] == NULL) {
                    continue;
                }

                if (j == 1) {
                    if (!g_strcmp0 (lines[j - 1], replace_from)) {
                        if (replace_to) {
                            string = g_string_append (string, replace_to);
                        } else {
                            // ignore the segment
                        }
                    } else {
                        string = g_string_append (string, lines[j - 1]);
                    }
                } else {
                    string = g_string_append (string, lines[j - 1]);
                }
            }
        }
    }
    new_line = g_string_free (string, FALSE);
    g_strfreev (lines);
    g_strfreev (formats);
    return new_line;
}

GString *
convert_contents (const gchar *contents, GHashTable *hash)
{
    GString *string = NULL;
    const gchar *p;
    const gchar *head;
    const gchar *line_break = NULL;
    gchar *line;
    gchar *new_line;

    string = g_string_new (NULL);
    for (p = contents; p && *p; p = g_utf8_next_char (p)) {
        line = NULL;
        head = p;
        if ((p = g_strstr_len (head, -1, "\r\n")) != NULL) {
            line = g_strndup (head, p - head + 1);
            line[p - head] = '\0';
            p++;
            line_break = "\r\n";
        } else if ((p = g_utf8_strchr (head, -1, '\n')) != NULL) {
            line = g_strndup (head, p - head + 1);
            line[p - head] = '\0';
            line_break = "\n";
        } else {
            line = g_strdup (head);
            line_break = NULL;
        }

        new_line = convert_line (line, hash);
        string = g_string_append (string, new_line);
        if (line_break) {
            string = g_string_append (string, line_break);
        }

#ifdef DEBUG
        g_printf ("%s\n", line);
        g_printf ("%s\n", new_line);
#endif
        g_free (line);
        g_free (new_line);
    }

    return string;
}

int
main (int argc, char *argv[])
{
    GOptionContext *context;
    GError *error = NULL;
    const gchar *parsed_file = NULL;
    gchar *contents = NULL;
    GHashTable *hash;
    GString *string = NULL;

    context = g_option_context_new ("--xml XML_FILE PARSED_FILE");
    g_option_context_add_main_entries (context, entries, "im-dict-ja");
    g_option_context_set_description (context,
        "  PARSED_FILE      parsed text file");
    g_option_context_set_summary (context, "summary");
    if (!g_option_context_parse (context, &argc, &argv, &error)) {
        g_printerr ("Option parse error: %s\n", error->message);
        return -1;
    }
    if (argc == 1 || !xml_file) {
        gchar *help = g_option_context_get_help (context, TRUE, NULL);
        g_print ("%s", help);
        g_free (help);
        return -1;
    }
    g_option_context_free (context);
    parsed_file = argv[1];
    contents = get_contents (parsed_file);
    if (contents == NULL) {
        return -1;
    }

    hash = parse_xml_file (xml_file);

#ifdef DEBUG
    g_print ("%s %s\n", "name", (gchar *) g_hash_table_lookup (hash, (gpointer) "name"));
    g_print ("%s %s\n", "format", (gchar *) g_hash_table_lookup (hash, (gpointer) "format"));
    g_print ("%s %s\n", "replace_from", (gchar *) g_hash_table_lookup (hash, (gpointer) "replace_from"));
    g_print ("%s %s\n", "replace_to", (gchar *) g_hash_table_lookup (hash, (gpointer) "replace_to"));
#endif

    string = convert_contents (contents, hash);

    g_hash_table_remove_all (hash);
    g_hash_table_destroy (hash);

    g_free (contents);

    contents = g_string_free (string, FALSE);
    g_printf ("%s", contents);
    g_free (contents);

    return 0;
}
