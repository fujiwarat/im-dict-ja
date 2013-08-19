/* vim:set et sts=4: */
/* im-dict-ja - Japanese word dictionary set for input method.
 * Copyright (C) 2010-2011 Takao Fujiwara <takao.fujiwara1@gmail.com>
 * Copyright (C) 2010-2011 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <glib.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include "xml-parse.h"

static const gchar *xml_file;

static void
parse_xml_content (xmlNodePtr node, const xmlChar *parent_name, GHashTable **table)
{
    xmlNodePtr current;
    gboolean has_content = FALSE;

    g_return_if_fail (parent_name != NULL);

    for (current = node; current; current = current->next) {
        if (current->type == XML_TEXT_NODE) {
            if (current->content) {
#ifdef DEBUG
                g_print ("%s %s\n", (char *) parent_name,
                                    (char *) current->content);
#endif
                g_hash_table_insert (*table,
                                     (gpointer) g_strdup ((char *) parent_name),
                                     (gpointer) g_strdup ((char *) current->content));
                has_content = TRUE;
                break;
            } else {
                g_error ("tag %s does not have content in the file %s",
                         (char *) parent_name,
                         xml_file);
            }
        }
    }
    if (!has_content) {
        g_error ("tag %s does not have content in the file %s",
                 (char *) parent_name,
                 xml_file);
    }
}

static void
parse_xml_attr (xmlAttrPtr node, const xmlChar* parent_name, GHashTable **ptable)
{
    xmlAttrPtr current;
    gboolean has_key = FALSE;

    for (current = node; current; current = current->next) {
        if (current->type == XML_ATTRIBUTE_NODE) {
            if (!g_strcmp0 ((char *) current->name, "name") ||
                !g_strcmp0 ((char *) current->name, "key") ||
                !g_strcmp0 ((char *) current->name, "value")) {
                if (current->children) {
                    parse_xml_content (current->children, current->name, ptable);
                    has_key = TRUE;
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
        }
    }
    if (!has_key) {
        g_error ("tag %s does not find \"key\" tag in file %s",
                 (char *) parent_name,
                 xml_file);
    }
}

static void
parse_xml_product (xmlNodePtr node, GHashTable **ptable)
{
    xmlNodePtr current;
    gboolean has_format = FALSE;

    for (current = node; current; current = current->next) {
        if (current->type == XML_ELEMENT_NODE) {
            if (!g_strcmp0 ((char *) current->name, "format")) {
                if (current->children) {
                    parse_xml_content (current->children, current->name, ptable);
                    has_format = TRUE;
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
            if (!g_strcmp0 ((char *) current->name, "replace_from")) {
#if 0
                if (current->properties) {
                    parse_xml_attr (current->properties, current->name, ptable);
                } else {
                    g_error ("tag %s does not have attributes in the file %s",
                             (char *) current->name,
                             xml_file);
                }
#endif
                if (current->children) {
                    parse_xml_content (current->children, current->name, ptable);
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
            if (!g_strcmp0 ((char *) current->name, "replace_to")) {
                if (current->children) {
                    parse_xml_content (current->children, current->name, ptable);
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
        }
    }
    if (!has_format) {
        g_error ("tag %s does not find \"format\" tag in file %s",
                 node->parent ? node->parent->name ? (char *) node->parent->name : "(null)" : "(null)",
                 xml_file);
    }
}

static void
parse_xml_im_dict (xmlNodePtr node, GHashTable **ptable)
{
    xmlNodePtr current;
    gboolean has_product_name = FALSE;
    gboolean has_product_child = FALSE;

    for (current = node; current; current = current->next) {
        if (current->type == XML_ELEMENT_NODE &&
            !g_strcmp0 ((char *) current->name, "product")) {
            if (current->properties) {
                parse_xml_attr (current->properties, current->name, ptable);
                has_product_name = TRUE;
            } else {
                g_error ("tag %s does not have attributes in the file %s",
                         (char *) current->name,
                         xml_file);
            }
            if (current->children) {
                parse_xml_product (current->children, ptable);
                has_product_child = TRUE;
                break;
            } else {
                g_error ("tag %s does not have child tags in the file %s",
                         (char *) current->name,
                         xml_file);
            }
        }
    }
    if (!has_product_name || !has_product_child) {
        g_error ("tag %s does not find \"product\" tag in file %s",
                 node->parent ? node->parent->name ? (char *) node->parent->name : "(null)" : "(null)",
                 xml_file);
    }
}

GHashTable *
parse_xml_file (const gchar *file)
{
    GHashTable *table = NULL;
    xmlDocPtr doc;
    xmlNodePtr node;

    xmlInitParser ();
    xmlLoadExtDtdDefaultValue = XML_DETECT_IDS | XML_COMPLETE_ATTRS;
    xmlSubstituteEntitiesDefault (1);

    xml_file = file;
    doc = xmlParseFile (xml_file);
    if (doc == NULL || xmlDocGetRootElement (doc) == NULL) {
        g_error ("Unable to parse file: %s", xml_file);
    }

    node = xmlDocGetRootElement (doc);
    if (node == NULL) {
        g_error ("Top node not found: %s", xml_file);
    }

    if (g_strcmp0 ((gchar *) node->name, "im-dict")) {
        g_error ("The first tag should be <im-dict>: %s", xml_file);
    }
    if (node->children == NULL) {
        g_error ("tag %s does not have child tags in the file %s",
                 (char *) node->name, xml_file);
    }

    table = g_hash_table_new (g_str_hash, g_str_equal);
    parse_xml_im_dict (node->children, &table);

    xmlFreeDoc (doc);
    xmlCleanupParser ();

    return table;
}
