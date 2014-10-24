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
 * $Id: CustomerRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerRecord.h>
#include <provided/CustomerRecord.h>

int CustomerRecord_isValueValid_alwaysAccept(const char * UNUSED(value)) {
    return 1;
}

void CustomerRecord_setValue_name(CustomerRecord * record, const char * value) {
    copyStringWithLength(record->name, value, CUSTOMERRECORD_NAME_SIZE);
    /*provided_CustomerRecord_setValue_name(record, value);*/
}

void CustomerRecord_setValue_address(CustomerRecord * record, const char * value) {
    copyStringWithLength(record->address, value, CUSTOMERRECORD_ADDRESS_SIZE);
    /*provided_CustomerRecord_setValue_address(record, value);*/
}

void CustomerRecord_setValue_postalCode(CustomerRecord * record, const char * value) {
    copyStringWithLength(record->postalCode, value, CUSTOMERRECORD_POSTALCODE_SIZE);
    /*provided_CustomerRecord_setValue_postalCode(record, value);*/
}

void CustomerRecord_setValue_town(CustomerRecord * record, const char * value) {
    copyStringWithLength(record->town, value, CUSTOMERRECORD_TOWN_SIZE);
    /*provided_CustomerRecord_setValue_town(record, value);*/
}

char * CustomerRecord_getValue_name(CustomerRecord * record) {
    return duplicateString(record->name);
    /*return provided_CustomerRecord_getValue_name(record);*/
}

char * CustomerRecord_getValue_address(CustomerRecord * record) {
    return duplicateString(record->address);
    /*return provided_CustomerRecord_getValue_address(record);*/
}

char * CustomerRecord_getValue_postalCode(CustomerRecord * record) {
    return duplicateString(record->postalCode);
    /*return provided_CustomerRecord_getValue_postalCode(record);*/
}

char * CustomerRecord_getValue_town(CustomerRecord * record) {
    return duplicateString(record->town);
    /*return provided_CustomerRecord_getValue_town(record);*/
}

static CustomerRecord_FieldProperties CustomerRecord_FieldsProperties[CUSTOMERRECORD_FIELDCOUNT] = {
        { CUSTOMERRECORD_NAME_SIZE, 200, "Nom", 0, CUSTOMERRECORD_NAME_SIZE - 1,
                CustomerRecord_isValueValid_alwaysAccept, CustomerRecord_setValue_name,
                CustomerRecord_getValue_name }, { CUSTOMERRECORD_ADDRESS_SIZE, 300, "Adresse", 0,
                CUSTOMERRECORD_ADDRESS_SIZE - 1, CustomerRecord_isValueValid_alwaysAccept,
                CustomerRecord_setValue_address, CustomerRecord_getValue_address }, {
                CUSTOMERRECORD_POSTALCODE_SIZE, 100, "Code portal", 0,
                CUSTOMERRECORD_POSTALCODE_SIZE - 1, CustomerRecord_isValueValid_alwaysAccept,
                CustomerRecord_setValue_postalCode, CustomerRecord_getValue_postalCode }, {
                CUSTOMERRECORD_TOWN_SIZE, 200, "Ville", 0, CUSTOMERRECORD_TOWN_SIZE - 1,
                CustomerRecord_isValueValid_alwaysAccept, CustomerRecord_setValue_town,
                CustomerRecord_getValue_town } };

CustomerRecord_FieldProperties CustomerRecord_getFieldProperties(int field) {
    if (field < 0 || field >= CUSTOMERRECORD_FIELDCOUNT)
        fatalError("CustomerRecord_GetFieldProperties: invalid index");
    return CustomerRecord_FieldsProperties[field];
}

void CustomerRecord_init(CustomerRecord * record) {
    int i;
    for(i = 0; i < CUSTOMERRECORD_NAME_SIZE; i++)
        record->name[i] = 0;
    for(i = 0; i < CUSTOMERRECORD_ADDRESS_SIZE; i++)
        record->address[i] = 0;
    for(i = 0; i < CUSTOMERRECORD_POSTALCODE_SIZE; i++)
        record->postalCode[i] = 0;
    for(i = 0; i < CUSTOMERRECORD_TOWN_SIZE; i++)
        record->town[i] = 0;
    /*provided_CustomerRecord_init(record);*/
}

void CustomerRecord_finalize(CustomerRecord * UNUSED(record)) {
    /*provided_CustomerRecord_finalize(record);*/
}

void CustomerRecord_read(CustomerRecord * record, FILE * file) {
	if(fread(record->name, CUSTOMERRECORD_NAME_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_read()read a name is error!");
	if(fread(record->address, CUSTOMERRECORD_ADDRESS_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_read()read an address is error!");
	if(fread(record->postalCode, CUSTOMERRECORD_POSTALCODE_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_read()read a postalcode is error!");
	if(fread(record->town, CUSTOMERRECORD_TOWN_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_read()read a town is error!");
    /*provided_CustomerRecord_read(record, file);*/
}

void CustomerRecord_write(CustomerRecord * record, FILE * file) {
    if(fwrite(record->name, CUSTOMERRECORD_NAME_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_write()write a name is error!");
	if(fwrite(record->address, CUSTOMERRECORD_ADDRESS_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_write()write an address is error!");
	if(fwrite(record->postalCode, CUSTOMERRECORD_POSTALCODE_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_write()write a postalcode is error!");
	if(fwrite(record->town, CUSTOMERRECORD_TOWN_SIZE, 1, file) != 1)
	    fatalError("CustomerRecord_write()write a name is error!");
    fflush(file);
    /*provided_CustomerRecord_write(record, file);*/
}

int CustomerRecord_edit(CustomerRecord * record) {
    GtkWidget *dialog;
    GtkWidget *hbox;
    GtkWidget *table;
    GtkWidget * entries[CUSTOMERRECORD_FIELDCOUNT];
    GtkWidget *label;
    gint response;
    guint i;
    gboolean valid;

    dialog = gtk_dialog_new_with_buttons("Edition d'un client", NULL, GTK_DIALOG_MODAL
            | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
            GTK_RESPONSE_CANCEL, NULL);

    hbox = gtk_hbox_new(FALSE, 8);
    gtk_container_set_border_width(GTK_CONTAINER (hbox), 8);
    gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox, FALSE, FALSE, 0);

    table = gtk_table_new(CUSTOMERRECORD_FIELDCOUNT, 2, FALSE);
    gtk_table_set_row_spacings(GTK_TABLE (table), 4);
    gtk_table_set_col_spacings(GTK_TABLE (table), 4);
    gtk_box_pack_start(GTK_BOX (hbox), table, TRUE, TRUE, 0);

    for (i = 0; i < CUSTOMERRECORD_FIELDCOUNT; ++i) {
        CustomerRecord_FieldProperties properties = CustomerRecord_getFieldProperties((int) i);
        char * content = properties.getValue(record);

        label = gtk_label_new(properties.name);
        gtk_table_attach_defaults(GTK_TABLE (table), label, 0, 1, i, i + 1);

        entries[i] = gtk_entry_new();

        gtk_entry_set_text(GTK_ENTRY (entries[i]), content);
        if (properties.maxlength != 0)
            gtk_entry_set_max_length(GTK_ENTRY (entries[i]), properties.maxlength);
        gtk_table_attach_defaults(GTK_TABLE (table), entries[i], 1, 2, i, i + 1);
        gtk_label_set_mnemonic_widget(GTK_LABEL (label), entries[i]);
        free(content);
    }

    gtk_widget_show_all(hbox);
    do {
        response = gtk_dialog_run(GTK_DIALOG (dialog));

        valid = (response == GTK_RESPONSE_OK);
        if (valid)
            for (i = 0; i < CUSTOMERRECORD_FIELDCOUNT; ++i) {
                CustomerRecord_FieldProperties properties =
                        CustomerRecord_getFieldProperties((int) i);
                if (!properties.isValueValid(gtk_entry_get_text(GTK_ENTRY (entries[i])))) {
                    GtkWidget *msgdialog;

                    msgdialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,
                            GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                            "Le contenu du champ \"%s\" est invalide", properties.name);
                    g_signal_connect (msgdialog, "response", G_CALLBACK (gtk_widget_destroy), NULL);
                    gtk_dialog_run(GTK_DIALOG (msgdialog));
                    valid = 0;
                    break;
                }
            }

        if (valid) {
            for (i = 0; i < CUSTOMERRECORD_FIELDCOUNT; ++i) {
                CustomerRecord_FieldProperties properties =
                        CustomerRecord_getFieldProperties((int) i);
                properties.setValue(record, gtk_entry_get_text(GTK_ENTRY (entries[i])));
            }
        }
    } while (response == GTK_RESPONSE_OK && !valid);

    gtk_widget_destroy(dialog);

    return (response == GTK_RESPONSE_OK && valid);
}
