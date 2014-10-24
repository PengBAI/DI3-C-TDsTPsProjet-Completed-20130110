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
 * $Id: Document.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Document.h>
#include <DocumentUtil.h>
#include <DocumentRowList.h>
#include <provided/Document.h>
#include <CustomerRecord.h>

/** Initialize a document
 * @param document a pointer to a document
 * @warning An initialized document must be finalized by Document_finalize() to free all resources
 */
void Document_init(Document * document) {
    CustomerRecord_init(&document->customer);
    document->editDate = duplicateString("");
    document->expiryDate = duplicateString("");
    document->docNumber = duplicateString("");
    document->object = duplicateString("");
    document->operator = duplicateString("");
    document->rows = NULL;
    document->typeDocument = QUOTATION;
    /*provided_Document_init(document);*/
}

/** Finalize a document
 * @param document the document to finalize
 * @warning document must have been initialized
 */
void Document_finalize(Document * document) {
    DocumentRow *row, *nextRow;
    free(document->editDate);
    document->editDate = NULL;
    free(document->expiryDate);
    document->expiryDate = NULL;
    free(document->docNumber);
    document->docNumber = NULL;
    free(document->object);
    document->object = NULL;
    free(document->operator);
    document->operator = NULL;

    row = document->rows;
    while(row != NULL)
    {
        nextRow = row->next;
        DocumentRow_destroy(row);
        row = nextRow;
    }
    document->rows = NULL;
    document = NULL;
    /*provided_Document_finalize(document);*/
}

/** Save the content of a document to a file
 * @param document the document
 * @param filename the file name
 * @warning document must have been initialized
 */
void Document_saveToFile(Document * document, const char * filename) {
    int rowCount;
    FILE * file;
    DocumentRow *row;
    if((file = fopen(filename, "wb+")) == NULL )
        fatalError("Document_saveToFile()open file is error!");

    CustomerRecord_write(&document->customer, file);
    writeString(document->editDate, file);
    writeString(document->expiryDate, file);
    writeString(document->docNumber, file);
    writeString(document->object, file);
    writeString(document->operator, file);

    rowCount = DocumentRowList_getRowCount(document->rows);
    if(fwrite(&rowCount, sizeof(int), 1, file) != 1)
        fatalError("Document_saveToFile() write row count is error!");
    row = document->rows;
    while(row != NULL)
    {
        DocumentRow_writeRow(row, file);
        row = row->next;
    }
    if(fwrite(&document->typeDocument, sizeof(int), 1, file) != 1)
        fatalError("Document_saveToFile fwrite Error!");
    fclose(file);
    /*provided_Document_saveToFile(document,filename);*/
}

/** Load the content of a document from a file
 * @param document the document to fill
 * @param filename the file name
 * @warning document must have been initialized
 */
void Document_loadFromFile(Document * document, const char * filename) {
    int rowCount;
    FILE * file;
    DocumentRow *tempRow, *nowRow;
    if((file = fopen(filename, "rb+")) == NULL )
        fatalError("Document_loadFromFile()open file is error!");

    CustomerRecord_read(&document->customer, file);
    document->editDate = readString(file);
    document->expiryDate = readString(file);
    document->docNumber = readString(file);
    document->object = readString(file);
    document->operator = readString(file);

    if(fread(&rowCount, sizeof(int), 1, file) != 1)
        fatalError("Document_loadFromFile() read a row count is error!");
    if(rowCount > 0)
    {
        document->rows = DocumentRow_readRow(file);
        nowRow = document->rows;
        while(rowCount - 1 != 0)
        {
            tempRow = DocumentRow_readRow(file);
            nowRow->next = tempRow;
            nowRow = nowRow->next;
            tempRow->next = NULL;
            rowCount--;
        }
    }
    if(fread(&(document->typeDocument), sizeof(int), 1, file) != 1)
        fatalError("Document_loadFromFile()read a typeDocument is error!");
    fclose(file);
    /*provided_Document_loadFromFile(document,filename);*/
}

