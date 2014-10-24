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
 * $Id: PrintFormat.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <PrintFormat.h>
#include <Dictionary.h>
#include <provided/PrintFormat.h>

/** Initialize a print format
 * @param format a print format
 * @warning initialized print format should be finalized with PrintFormat_finalize()
 */
void PrintFormat_init(PrintFormat * format) {
    format->name = duplicateString("");
    format->header = duplicateString("");
    format->row = duplicateString("");
    format->footer = duplicateString("");
    /*provided_PrintFormat_init(format);*/
}

/** Finalize a print format
 * @param format the print format
 */
void PrintFormat_finalize(PrintFormat * format) {
    free(format->name);
    format->name = NULL;
    free(format->header);
    format->header = NULL;
    free(format->row);
    format->row = NULL;
    free(format->footer);
    format->footer = NULL;
    /*provided_PrintFormat_finalize(format);*/
}

/** return a line on the heap which is read from the file
 * @param ficher file is opened
 * @return a string read from the file
 */
static char * readLine(FILE * ficher){
    size_t readLength;
    char *newLine = duplicateString("");
    char readText[1024];
    char *tempLine;
    while(fgets(readText, 1024, ficher) != NULL)
    {
        readLength = stringLength(readText);
        tempLine = concatenateString(newLine, readText);
        free(newLine);
        newLine = tempLine;
        if(readText[readLength - 1] == '\n')
            return newLine;
    }
    return newLine;
}

/** Load a print format from a file
 * @param format an initialized print format to fill
 * @param filename the file name
 */
void PrintFormat_loadFromFile(PrintFormat * format, const char * filename) {
    char *nameLine, *headerLine, *rowLine, *footerLine;
    char *tempHeaderLine, *tempRowLine, *tempFooterLine;
    char *newHeaderLine, *newRowLine, *newFooterLine;
    FILE *file;
    headerLine = duplicateString("");
    rowLine = duplicateString("");
    footerLine = duplicateString("");

    file = fopen(filename, "rt");
    if(file != NULL)
    {
        /* Phase 1 : .NAME */
        nameLine = readLine(file);
        free(format->name);
        format->name = subString(nameLine + 6,nameLine + stringLength(nameLine));
        format->name[stringLength(format->name) - 1] = '\0';
        /* Phase 2 : .HEADER */
        do{
            tempHeaderLine = readLine(file);
            newHeaderLine = concatenateString(headerLine,tempHeaderLine);
            free(headerLine);
            headerLine = newHeaderLine;
        }while(compareString(tempHeaderLine, ".ROW\n") != 0);
        free(format->header);
        format->header = subString(headerLine + 8, headerLine + stringLength(headerLine));
        format->header[stringLength(format->header) - 6] = '\0';
        /* Phase 3 : .ROW */
        do{
            tempRowLine = readLine(file);
            newRowLine = concatenateString(rowLine, tempRowLine);
            free(rowLine);
            rowLine = newRowLine;
        }while(compareString(tempRowLine, ".FOOTER\n") != 0);
        free(format->row);
        format->row = subString(rowLine, rowLine + stringLength(rowLine));
        format->row[stringLength(format->row) - 9] = '\0';
        /* Phase 4 : .FOOTER */
        do{
            tempFooterLine = readLine(file);
            if(compareString(tempFooterLine, ".END\n") == 0)
                tempFooterLine[4] = '\0';
            newFooterLine = concatenateString(footerLine,tempFooterLine);
            free(footerLine);
            footerLine = newFooterLine;
        }while(compareString(tempFooterLine, ".END") != 0);
        free(format->footer);
        format->footer = subString(footerLine, footerLine + stringLength(footerLine));
        format->footer[stringLength(format->footer) - 5] = '\0';
    }
    free(headerLine);
    free(rowLine);
    free(footerLine);
    /*provided_PrintFormat_loadFromFile(format, filename);*/
}

/** Format a document according to a print format
 * @param document the document
 * @param printFormat the print format
 * @return a new string created on the heap containing the formatted document
 * @warning The user is responsible for freeing the memory
 */
char * formatDocument(Document * document, PrintFormat * printFormat) {
    Dictionary * dictionary;
    char * result;
    char * temp, *formatted;
    DocumentRow * row;
    double totalHT, totalTVA, totalTTC;

    /* Phase 1 : entete */
    dictionary = Dictionary_create();
    Dictionary_setStringEntry(dictionary, "CUSTOMER.NAME", document->customer.name);
    Dictionary_setStringEntry(dictionary, "CUSTOMER.ADDRESS", document->customer.address);
    Dictionary_setStringEntry(dictionary, "CUSTOMER.PORTALCODE", document->customer.postalCode);
    Dictionary_setStringEntry(dictionary, "CUSTOMER.TOWN", document->customer.town);
    Dictionary_setStringEntry(dictionary, "DOCNUMBER", document->docNumber);
    Dictionary_setStringEntry(dictionary, "EDITDATE", document->editDate);
    Dictionary_setStringEntry(dictionary, "OBJECT", document->object);
    Dictionary_setStringEntry(dictionary, "OPERATOR", document->operator);
    Dictionary_setStringEntry(dictionary, "EXPIRYDATE", document->expiryDate);
    if (document->typeDocument == QUOTATION)
        Dictionary_setStringEntry(dictionary, "TYPEDOCUMENT", "Devis");
    else
        Dictionary_setStringEntry(dictionary, "TYPEDOCUMENT", "Facture");

    result = Dictionary_format(dictionary, printFormat->header);
    temp = concatenateString(result, "\n");
    free(result);
    result = temp;
    Dictionary_destroy(dictionary);

    /* Phase 2 : les lignes */
    row = document->rows;
    totalTVA = 0;
    totalHT = 0;
    totalTTC = 0;
    while (row != NULL) {
        dictionary = Dictionary_create();
        Dictionary_setStringEntry(dictionary, "CODE", row->code);
        Dictionary_setStringEntry(dictionary, "DESIGNATION", row->designation);
        Dictionary_setStringEntry(dictionary, "UNITY", row->unity);
        Dictionary_setNumberEntry(dictionary, "BASEPRICE", row->basePrice);
        Dictionary_setNumberEntry(dictionary, "SELLINGPRICE", row->sellingPrice);
        Dictionary_setNumberEntry(dictionary, "QUANTITY", row->quantity);
        Dictionary_setNumberEntry(dictionary, "DISCOUNT", row->discount);
        Dictionary_setNumberEntry(dictionary, "RATEOFVAT", row->rateOfVAT);
        Dictionary_setNumberEntry(dictionary, "SOLDPRICE", row->sellingPrice - row->discount);
        Dictionary_setNumberEntry(dictionary, "VAT", (row->sellingPrice - row->discount)
                * row->rateOfVAT / 100.);
        Dictionary_setNumberEntry(dictionary, "FINALPRICE", (row->sellingPrice - row->discount)
                * (1. + row->rateOfVAT / 100.));
        totalHT += row->quantity * (row->sellingPrice - row->discount);
        totalTVA += row->quantity * (row->sellingPrice - row->discount) * row->rateOfVAT / 100.;
        totalTTC += row->quantity * (row->sellingPrice - row->discount) * (1. + row->rateOfVAT / 100.);

        formatted = Dictionary_format(dictionary, printFormat->row);
        temp = concatenateString(result, formatted);
        free(formatted);
        free(result);
        result = temp;
        Dictionary_destroy(dictionary);
        row = row->next;

        temp = concatenateString(result, "\n");
        free(result);
        result = temp;
    }

    dictionary = Dictionary_create();
    Dictionary_setNumberEntry(dictionary, "SUMWITHOUTVAT", totalHT);
    Dictionary_setNumberEntry(dictionary, "SUMOFVAT", totalTVA);
    Dictionary_setNumberEntry(dictionary, "SUMWITHVAT", totalTTC);
    formatted = Dictionary_format(dictionary, printFormat->footer);
    temp = concatenateString(result, formatted);
    free(formatted);
    free(result);
    result = temp;

    temp = concatenateString(result, "\n");
    free(result);
    result = temp;
    Dictionary_destroy(dictionary);

    return result;
}
