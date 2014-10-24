/*
 * Copyright 2010 Sébastien Aupetit <sebastien.aupetit@univ-tours.fr>
 *
 * This source code is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this source code. If not, see <http://www.gnu.org/licenses/>.
 *
 * $Id: Print.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Print.h>
#include <PrintFormat.h>

/** Create a combo box of all the models
 * @return the combo box
 */
static GtkWidget * PrintPreview_getComboOfModels(void) {
    GtkWidget * combo;
    GDir * directory;

    combo = gtk_combo_box_new_text();

    directory = g_dir_open("..", 0, NULL);
    if (directory == NULL) {
        GtkWidget *errordialog;
        errordialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Impossible de lister les formats");
        g_signal_connect (errordialog, "response", G_CALLBACK (gtk_widget_destroy), NULL);
        gtk_widget_show(errordialog);
    } else {
        const gchar * entry;
        while ((entry = g_dir_read_name(directory)) != NULL) {
            if (icaseStartWith("printformat-", entry) && icaseEndWith(".txt", entry)) {
                char * temp = duplicateString(entry + strlen("printformat-"));
                temp[strlen(temp) - 4] = '\0';
                gtk_combo_box_append_text(GTK_COMBO_BOX(combo), temp);
                free(temp);
            }
        }
        g_dir_close(directory);
    }

    return combo;
}

/** Structure used to easy the transmission of data to the signal handlers
 * @internal
 */
typedef struct {
    GtkWidget * viewer;
    Document * document;
} PrintContext;

/** Signal handler which handles the combo box changes
 * @param combo the combo box
 * @param context the context
 */
static void PrintPreview_comboChanged(GtkComboBox *combo, PrintContext * context) {
    GtkTextBuffer *buffer;
    char * content;
    PrintFormat format;
    char buf[1024];
    GtkTextIter iter;
    gchar * selected = gtk_combo_box_get_active_text(combo);
    if (selected != NULL) {
        PrintFormat_init(&format);
        sprintf(buf, "../printformat-%s.txt", selected);
        PrintFormat_loadFromFile(&format, buf);

        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (context->viewer));
        content = formatDocument(context->document, &format);

        gtk_text_buffer_set_text(buffer,"",-1);

        gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
        gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, content, -1,
                              "font", NULL);
        free(content);

        PrintFormat_finalize(&format);
        g_free(selected);
    }
}

/** Display a dialog showing a print preview of the document
 * @param document the document
 */
void Print_preview(Document * document) {
    GtkWidget * dialog;
    GtkWidget *sw, *combo;
    PrintContext context;
    GtkTextBuffer *buffer;

    context.document = document;

    dialog = gtk_dialog_new_with_buttons("Aperçu d'impression du document", NULL, GTK_DIALOG_MODAL
            | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(dialog), 5);

    gtk_container_set_border_width(GTK_CONTAINER(GTK_DIALOG (dialog)->vbox), 5);

    combo = PrintPreview_getComboOfModels();
    gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->vbox), combo, TRUE, TRUE, 5);
    g_signal_connect(G_OBJECT(combo), "changed", G_CALLBACK(PrintPreview_comboChanged), &context);

    context.viewer = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (context.viewer), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW (context.viewer), FALSE);
    gtk_widget_set_size_request(context.viewer, 800, 600);
    gtk_widget_set_can_focus(context.viewer, FALSE);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (context.viewer));
    /* Tag with font fixed and tag name "font". */
    gtk_text_buffer_create_tag(buffer, "font", "family", "monospace", NULL);

    sw = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC,
            GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER (sw), context.viewer);
    gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->vbox), sw, TRUE, TRUE, 0);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

    gtk_widget_show_all(GTK_DIALOG (dialog)->vbox);
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);
}
