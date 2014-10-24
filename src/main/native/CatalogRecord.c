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
 * $Id: CatalogRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogRecord.h>
#include <provided/CatalogRecord.h>

/** Static function which always accepts the value
 * @param value the value to test
 * @return true
 */
static int CatalogRecord_isValueValid_alwaysAccept(const char * value);

static int CatalogRecord_isValueValid_alwaysAccept(const char * UNUSED( value)) {
    return 1;
}

/** Static function which test if a code only contains numbers and letters
 * @param  value the value to test
 * @return true if the code is valid, false otherwise
 */
int CatalogRecord_isValueValid_code(const char * value) {
    int i,result;
    for(i = 0; value[i] != '\0'; i++)
    {
        if(value[i] <= '9' && value[i] >= '0')
            result = TRUE;
        else if(value[i] <= 'Z' && value[i] >= 'A')
            result = TRUE;
        else if(value[i] <= 'z' && value[i] >= 'a')
            result = TRUE;
        else
            return FALSE;
    }
    return result;
    /*return provided_CatalogRecord_isValueValid_code(value);*/
}

/** Static function which test if the value is a positive number
 * @param  value the value to test
 * @return true if the valie is valid, false otherwise
 */
int CatalogRecord_isValueValid_positiveNumber(const char * value) {
    double testValue;
    char *endptr;
    testValue = strtod(value, &endptr);
    if(testValue > 0 && *endptr == '\0')
        return TRUE;
    else
        return FALSE;
    /*return provided_CatalogRecord_isValueValid_positiveNumber(value);*/
}

/** Static function to set the code field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CatalogRecord_setValue_code(CatalogRecord * record, const char * value) {
    copyStringWithLength(record->code, value, CATALOGRECORD_CODE_SIZE);
    /*provided_CatalogRecord_setValue_code(record, value);*/
}

/** Static function to set the designation field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CatalogRecord_setValue_designation(CatalogRecord * record, const char * value) {
    copyStringWithLength(record->designation, value, CATALOGRECORD_DESIGNATION_SIZE);
    /*provided_CatalogRecord_setValue_designation(record, value);*/
}

/** Static function to set the unity field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CatalogRecord_setValue_unity(CatalogRecord * record, const char * value) {
    copyStringWithLength(record->unity, value, CATALOGRECORD_UNITY_SIZE);
    /*provided_CatalogRecord_setValue_unity(record, value);*/
}

/** Static function to set the basePrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CatalogRecord_setValue_basePrice(CatalogRecord * record, const char * value) {
    if(CatalogRecord_isValueValid_positiveNumber(value) == 1)
        record->basePrice = strtod(value, NULL);
    /*provided_CatalogRecord_setValue_basePrice(record, value);*/
}

/** Static function to set the sellingPrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CatalogRecord_setValue_sellingPrice(CatalogRecord * record, const char * value) {
    if(CatalogRecord_isValueValid_positiveNumber(value) == 1)
        record->sellingPrice = strtod(value, NULL);
    /*provided_CatalogRecord_setValue_sellingPrice(record, value);*/
}

/** Static function to set the rateOfVAT field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CatalogRecord_setValue_rateOfVAT(CatalogRecord * record, const char * value) {
    if(CatalogRecord_isValueValid_positiveNumber(value) == 1)
        record->rateOfVAT = strtod(value, NULL);
    /*provided_CatalogRecord_setValue_rateOfVAT(record, value);*/
}

/** Static function which create a copy string on the head of the code field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogRecord_getValue_code(CatalogRecord * record) {
    return duplicateString(record->code);
    /*return provided_CatalogRecord_getValue_code(record);*/
}

/** Static function which create a copy string on the head of the designation field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogRecord_getValue_designation(CatalogRecord * record) {
    return duplicateString(record->designation);
    /*return provided_CatalogRecord_getValue_designation(record);*/
}

/** Static function which create a copy string on the head of the unity field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogRecord_getValue_unity(CatalogRecord * record) {
    return duplicateString(record->unity);
    /*return provided_CatalogRecord_getValue_unity(record);*/
}

/** Static function which create a copy string on the head of the basePrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogRecord_getValue_basePrice(CatalogRecord * record) {
    char *tempBasePrice;
    tempBasePrice = (char *)malloc(CATALOGRECORD_BASEPRICE_SIZE * sizeof(char));
    if(tempBasePrice == NULL)
        fatalError("CatalogRecord_getValue_basePrice() calloc is error!");
    sprintf(tempBasePrice, "%.2f", record->basePrice);
    return tempBasePrice;
    /*return provided_CatalogRecord_getValue_basePrice(record);*/
}

/** Static function which create a copy string on the head of the sellingPrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogRecord_getValue_sellingPrice(CatalogRecord * record) {
    char *tempSellingPrice;
    tempSellingPrice = (char *)malloc(CATALOGRECORD_SELLINGPRICE_SIZE * sizeof(char));
    if(tempSellingPrice == NULL)
        fatalError("CatalogRecord_getValue_sellingPrice() calloc is error!");
    sprintf(tempSellingPrice, "%.2f", record->sellingPrice);
    return tempSellingPrice;
    /*return provided_CatalogRecord_getValue_sellingPrice(record);*/
}

/** Static function which create a copy string on the head of the rateOfVAT field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogRecord_getValue_rateOfVAT(CatalogRecord * record) {
    char *tempRateOfVAT;
    tempRateOfVAT = (char *)malloc(CATALOGRECORD_RATEOFVAT_SIZE * sizeof(char));
    if(tempRateOfVAT == NULL)
        fatalError("CatalogRecord_getValue_rateOfVAT() calloc is error!");
    sprintf(tempRateOfVAT, "%.2f", record->rateOfVAT);
    return tempRateOfVAT;
    /*return provided_CatalogRecord_getValue_rateOfVAT(record);*/
}

/** Static registry for field descriptions */
static CatalogRecord_FieldProperties CatalogRecord_fieldsProperties[CATALOGRECORD_FIELDCOUNT] = {
        { CATALOGRECORD_CODE_SIZE, 100, "Code", 0, CATALOGRECORD_CODE_SIZE - 1,
                CatalogRecord_isValueValid_code, CatalogRecord_setValue_code,
                CatalogRecord_getValue_code }, { CATALOGRECORD_DESIGNATION_SIZE, 300,
                "Désignation", 0, CATALOGRECORD_DESIGNATION_SIZE - 1,
                CatalogRecord_isValueValid_alwaysAccept, CatalogRecord_setValue_designation,
                CatalogRecord_getValue_designation }, { CATALOGRECORD_UNITY_SIZE, 100, "Unité",
                0.5, CATALOGRECORD_UNITY_SIZE - 1, CatalogRecord_isValueValid_alwaysAccept,
                CatalogRecord_setValue_unity, CatalogRecord_getValue_unity }, {
                CATALOGRECORD_BASEPRICE_SIZE, 100, "Prix de revient", 1, 10,
                CatalogRecord_isValueValid_positiveNumber, CatalogRecord_setValue_basePrice,
                CatalogRecord_getValue_basePrice }, { CATALOGRECORD_SELLINGPRICE_SIZE, 100,
                "Prix de vente", 1, 10, CatalogRecord_isValueValid_positiveNumber,
                CatalogRecord_setValue_sellingPrice, CatalogRecord_getValue_sellingPrice }, {
                CATALOGRECORD_RATEOFVAT_SIZE, 100, "Taux TVA (en %)", 1, 10,
                CatalogRecord_isValueValid_positiveNumber, CatalogRecord_setValue_rateOfVAT,
                CatalogRecord_getValue_rateOfVAT } };

/** Get a copy of the properties of a field
 * @param field the identifier of the field
 * @return the properties
 * @see CatalogRecord_FieldIdentifier
 */
CatalogRecord_FieldProperties CatalogRecord_getFieldProperties(int field) {
    if (field < 0 || field >= CATALOGRECORD_FIELDCOUNT)
        fatalError("CatalogRecord_GetFieldProperties: invalid index");
    return CatalogRecord_fieldsProperties[field];
}

/** Initialize a record
 * @param[in] record a pointer to a record to initialize
 * @warning every initialized record must be finalized with CatalogRecord_finalize()
 */
void CatalogRecord_init(CatalogRecord * record) {
    record->code = (char *)calloc(sizeof(char),CATALOGRECORD_CODE_SIZE);
    if(record->code == NULL)
        fatalError("CatalogRecord_init() calloc code is error!");
    record->designation = (char *)calloc(sizeof(char),CATALOGRECORD_DESIGNATION_SIZE);
    if(record->designation == NULL)
        fatalError("CatalogRecord_init() calloc designation is error!");
    record->unity = (char *)calloc(sizeof(char),CATALOGRECORD_UNITY_SIZE);
    if(record->unity == NULL)
        fatalError("CatalogRecord_init() calloc unity is error!");
    record->basePrice = 0;
    record->sellingPrice = 0;
    record->rateOfVAT = 0;
    /*provided_CatalogRecord_init(record);*/
}

/** Finalize a record.
 * @param[in] record a pointer to a record to finalize
 */
void CatalogRecord_finalize(CatalogRecord * record) {
    free(record->code);
    record->code = NULL;
    free(record->designation);
    record->designation = NULL;
    free(record->unity);
    record->unity = NULL;
    /*provided_CatalogRecord_finalize(record);*/
}

/** Read a record from a file
 * @param record a pointer to an initialized record on which to store data
 * @param file the file from which the data are read
 */
void CatalogRecord_read(CatalogRecord * record, FILE * file) {
    if((fread(record->code, CATALOGRECORD_CODE_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_read()read code is error!");
    if((fread(record->designation, CATALOGRECORD_DESIGNATION_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_read()read designation is error!");
    if((fread(record->unity, CATALOGRECORD_UNITY_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_read()read unity is error!");
    if((fread(&record->basePrice, CATALOGRECORD_BASEPRICE_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_read()read basePrice is error!");
    if((fread(&record->sellingPrice, CATALOGRECORD_SELLINGPRICE_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_read()read sellingPrice is error!");
    if((fread(&record->rateOfVAT, CATALOGRECORD_RATEOFVAT_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_read()read rateOfVAT is error!");
    /*provided_CatalogRecord_read(record, file);*/
}

/** Write a record to a file
 * @param record a pointer to a record
 * @param file the file to which the data are written
 */
void CatalogRecord_write(CatalogRecord * record, FILE * file) {
    if((fwrite(record->code, CATALOGRECORD_CODE_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_write()write code is error!");
    if((fwrite(record->designation, CATALOGRECORD_DESIGNATION_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_write()write designation is error!");
    if((fwrite(record->unity, CATALOGRECORD_UNITY_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_write()write unity is error!");
    if((fwrite(&record->basePrice, CATALOGRECORD_BASEPRICE_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_write()write basePrice is error!");
    if((fwrite(&record->sellingPrice, CATALOGRECORD_SELLINGPRICE_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_write()write sellingPrice is error!");
    if((fwrite(&record->rateOfVAT, CATALOGRECORD_RATEOFVAT_SIZE, 1, file)) != 1)
        fatalError("CatalogRecord_write()write rateOfVAT is error!");
    /*provided_CatalogRecord_write(record, file);*/
}

/** CatalogRecordEditor structure
 * @internal
 */
typedef struct _CatalogRecordEditor {
    GtkWidget * entries[CATALOGRECORD_FIELDCOUNT];
    gulong insert_text_handler[CATALOGRECORD_FIELDCOUNT];
    CatalogRecord * record;
} CatalogRecordEditor;

/** Compute the field id associated with an entry
 * @param catalogRecordEditor a pointer on the CatalogRecordEditor structure
 * @param entry the entry to associate with an id
 * @return the field id
 */
static int CatalogRecordEditor_getEntryOffset(CatalogRecordEditor * catalogRecordEditor,
        GtkWidget * entry) {
    int i;
    for (i = 0; i < CATALOGRECORD_FIELDCOUNT; ++i)
        if (catalogRecordEditor->entries[i] == entry)
            return i;
    return -1;
}

/** Static handler to validate input for entries
 * @see insert_text signal of GtkEntry (GTK+)
 */
static void CatalogRecordEditor_insert_text_handler(GtkWidget *entry, const gchar *text,
        gint length, gint *position, CatalogRecordEditor * catalogRecordEditor) {
    int offset = CatalogRecordEditor_getEntryOffset(catalogRecordEditor, entry);
    CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(offset);
    const char * allText = gtk_entry_get_text(GTK_ENTRY(entry));
    char * result = insertString(allText, *position, text, length);

    GtkEditable *editable = GTK_EDITABLE(entry);

    if (properties.isValueValid(result)) {
        g_signal_handler_block(G_OBJECT (editable),
                catalogRecordEditor->insert_text_handler[offset]);
        gtk_editable_insert_text(editable, text, length, position);
        g_signal_handler_unblock(G_OBJECT (editable),
                catalogRecordEditor->insert_text_handler[offset]);
    }
    g_signal_stop_emission_by_name(G_OBJECT (editable), "insert_text");
    free(result);
}

/** Static handler to format input for entries
 * @see focus-out-event signal of GtkEntry (GTK+)
 */
static gboolean CatalogRecordEditor_focus_out_event(GtkEntry * entry,
        GdkEventFocus * UNUSED( event), CatalogRecordEditor * catalogRecordEditor) {
    CatalogRecord record;
    int offset = CatalogRecordEditor_getEntryOffset(catalogRecordEditor, GTK_WIDGET(entry));
    CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(offset);
    CatalogRecord_init(&record);

    properties.setValue(&record, gtk_entry_get_text(entry));
    gtk_entry_set_text(entry, properties.getValue(&record));

    CatalogRecord_finalize(&record);
    return FALSE;
}

/** Edit a record
 * @param record a pointer to the record to edit
 * @return a non null value if the changes were valided, 0 otherwise
 */
int CatalogRecord_edit(CatalogRecord * record) {
    GtkWidget *dialog;
    GtkWidget *hbox;
    GtkWidget *table;
    GtkWidget *label;
    gint response;
    int i;
    gboolean valid;
    CatalogRecordEditor catalogRecordEditor;

    catalogRecordEditor.record = record;

    dialog = gtk_dialog_new_with_buttons("Edition d'un produit", NULL, GTK_DIALOG_MODAL
            | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
            GTK_RESPONSE_CANCEL, NULL);

    hbox = gtk_hbox_new(FALSE, 8);
    gtk_container_set_border_width(GTK_CONTAINER (hbox), 8);
    gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox, FALSE, FALSE, 0);

    table = gtk_table_new(CATALOGRECORD_FIELDCOUNT, 2, FALSE);
    gtk_table_set_row_spacings(GTK_TABLE (table), 4);
    gtk_table_set_col_spacings(GTK_TABLE (table), 4);
    gtk_box_pack_start(GTK_BOX (hbox), table, TRUE, TRUE, 0);

    for (i = 0; i < CATALOGRECORD_FIELDCOUNT; ++i) {
        CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties((int) i);
        char * content = properties.getValue(record);

        label = gtk_label_new(properties.name);
        gtk_table_attach_defaults(GTK_TABLE (table), label, 0, 1, (guint) i, (guint) i + 1);

        catalogRecordEditor.entries[i] = gtk_entry_new();

        gtk_entry_set_text(GTK_ENTRY (catalogRecordEditor.entries[i]), content);
        if (properties.maxlength != 0)
            gtk_entry_set_max_length(GTK_ENTRY (catalogRecordEditor.entries[i]),
                    properties.maxlength);
        catalogRecordEditor.insert_text_handler[i]
                = g_signal_connect(G_OBJECT(catalogRecordEditor.entries[i]), "insert_text", G_CALLBACK(CatalogRecordEditor_insert_text_handler), &catalogRecordEditor);
        g_signal_connect(G_OBJECT(catalogRecordEditor.entries[i]), "focus-out-event", G_CALLBACK(CatalogRecordEditor_focus_out_event), &catalogRecordEditor);

        gtk_table_attach_defaults(GTK_TABLE (table), catalogRecordEditor.entries[i], 1, 2,
                (guint) i, (guint) i + 1);
        gtk_label_set_mnemonic_widget(GTK_LABEL (label), catalogRecordEditor.entries[i]);
        free(content);
    }

    gtk_widget_show_all(hbox);
    do {
        response = gtk_dialog_run(GTK_DIALOG (dialog));

        valid = (response == GTK_RESPONSE_OK);
        if (valid)
            for (i = 0; i < CATALOGRECORD_FIELDCOUNT; ++i) {
                CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(i);
                if (!properties.isValueValid(gtk_entry_get_text(
                        GTK_ENTRY (catalogRecordEditor.entries[i])))) {
                    GtkWidget * msgdialog = gtk_message_dialog_new(NULL,
                            GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                            "Le contenu du champ \"%s\" est invalide", properties.name);
                    g_signal_connect (msgdialog, "response", G_CALLBACK (gtk_widget_destroy), NULL);
                    gtk_dialog_run(GTK_DIALOG (msgdialog));
                    valid = 0;
                    break;
                }
            }

        if (valid) {
            for (i = 0; i < CATALOGRECORD_FIELDCOUNT; ++i) {
                CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(i);
                properties.setValue(record, gtk_entry_get_text(
                        GTK_ENTRY (catalogRecordEditor.entries[i])));
            }
        }
    } while (response == GTK_RESPONSE_OK && !valid);

    gtk_widget_destroy(dialog);

    return (response == GTK_RESPONSE_OK && valid);
}
