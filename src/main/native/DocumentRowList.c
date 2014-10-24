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
 * $Id: DocumentRowList.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentRowList.h>
#include <DocumentUtil.h>
#include <provided/DocumentRowList.h>

/** Initialize a row
 * @param row the row
 * @warning an initialized row must be finalized by DocumentRow_finalize() to free all resources
 */
void DocumentRow_init(DocumentRow * row) {
    row->code = duplicateString("");
    row->designation = duplicateString("");
    row->quantity = 0;
    row->unity = duplicateString("");
    row->basePrice = 0;
    row->sellingPrice = 0;
    row->discount = 0;
    row->rateOfVAT = 0;
    row->next = NULL;
    /*provided_DocumentRow_init(row);*/
}

/** Finalize a row
 * @param row the row
 * @warning document must have been initialized
 */
void DocumentRow_finalize(DocumentRow * row) {
    free(row->code);
    row->code = NULL;
    free(row->designation);
    row->designation = NULL;
    free(row->unity);
    row->unity = NULL;
    /*provided_DocumentRow_finalize(row);*/
}

/** Create a new row on the heap and initialize it
 * @return the new row
 */
DocumentRow * DocumentRow_create(void) {
    DocumentRow *newRow;
    newRow = (DocumentRow *)malloc(sizeof(DocumentRow));
    if(newRow == NULL)
        fatalError("creat document row is error!");
    DocumentRow_init(newRow);
    return newRow;
    /*return provided_DocumentRow_create();*/
}

/** Finalize and destroy a row previously created on the heap
 * @param row the row
 */
void DocumentRow_destroy(DocumentRow * row) {
    DocumentRow_finalize(row);
    free(row);
    row = NULL;
    /*provided_DocumentRow_destroy(row);*/
}

/** Initialize a list of rows
 * @param list the address of the pointer on the first cell of the list
 */
void DocumentRowList_init(DocumentRow ** list) {
    *list = NULL;
    /*provided_DocumentRowList_init(list);*/
}

/** Finalize a list of rows
 * @param list the address of the pointer on the first cell of the list
 * @note Each row of the list are destroyer using DocumentRow_destroy()
 */
void DocumentRowList_finalize(DocumentRow ** list) {
    if(*list != NULL)
    {
        DocumentRow *last;
        last = NULL;
        while((*list)->next != NULL)
        {
            last = (*list);
            (*list) = (*list)->next;
            DocumentRow_destroy(last);
        }
        DocumentRow_destroy(*list);
    }
    *list = NULL;
    /*provided_DocumentRowList_finalize(list);*/
}

/** Get a pointer on the rowIndex-th row of the list
 * @param list the pointer on the first cell of the list
 * @param rowIndex the index of the requested row
 * @return a pointer on the rowIndex-th row of the list or NULL if the list contains less rows than the requested one
 */
DocumentRow * DocumentRowList_get(DocumentRow * list, int rowIndex) {
    while(0 < rowIndex)
    {
        if(list != NULL)
            list = list->next;
        else
            return NULL;
        rowIndex--;
    }
    return list;
    /*return provided_DocumentRowList_get(list, rowIndex);*/
}

/**
 * Get the number of rows in the list
 * @param list the pointer on the first cell of the list
 */
int DocumentRowList_getRowCount(DocumentRow * list) {
    int i = 0;
    while(list != NULL)
    {
        list = list->next;
        i++;
    }
    return i;
    /*return provided_DocumentRowList_getRowCount(list);*/
}

/** Add a row at the end of the list
 * @param list the address of the pointer on the first cell of the list
 * @param row the row to add
 */
void DocumentRowList_pushBack(DocumentRow ** list, DocumentRow * row) {
    if((*list) == NULL)
    {
        (*list) = row;
    }
    else
    {
        DocumentRow *now;
        now = *list;
        while(now->next != NULL)
        {
            now = now->next;
        }
        now->next = row;
    }
    /*provided_DocumentRowList_pushBack(list, row);*/
}

/** Insert a row before a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void DocumentRowList_insertBefore(DocumentRow ** list, DocumentRow * position, DocumentRow * row) {
    if(*list == position)
    {
        *list = row;
        row->next = position;
    }
    else
    {
        DocumentRow *now;
        now = *list;
        while(now->next != position)
        {
            now = now->next;
        }
        now->next = row;
        row->next = position;
    }
    /*provided_DocumentRowList_insertBefore(list, position, row);*/
}

/** Insert a row after a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void DocumentRowList_insertAfter(DocumentRow ** list, DocumentRow * position, DocumentRow * row) {
    DocumentRow *now, *last;
    now = *list;
    last = NULL;
    while(last != position)
    {
        last = now;
        now = now->next;
    }
    last->next = row;
    row->next = now;
    /*provided_DocumentRowList_insertAfter(list, position, row);*/
}

/** Remove a row from the list
 * @param list the address of the pointer on the first cell of the list
 * @param position the row to remove
 */
void DocumentRowList_removeRow(DocumentRow ** list, DocumentRow * position) {
    DocumentRow *now;
    now = *list;
    if(now == position)
    {
        *list = position->next;
        DocumentRow_destroy(position);
    }
    else
    {
        while(now->next != position)
        {
            now = now->next;
        }
        now->next = position->next;
        DocumentRow_destroy(position);
    }
    /*provided_DocumentRowList_removeRow(list, position);*/
}

/** Write a row in a binary file
 * @param row the row
 * @param file the opened file
 */
void DocumentRow_writeRow(DocumentRow * row, FILE * file) {
    writeString(row->code, file);
    writeString(row->designation, file);
    if(fwrite(&row->quantity, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_writeRow() write quantity is error!");
    writeString(row->unity, file);
    if(fwrite(&row->basePrice, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_writeRow() write basePrice is error!");
    if(fwrite(&row->sellingPrice, sizeof(double),1, file) != 1 )
        fatalError("DocumentRow_writeRow() write sellingPrice is error!");
    if(fwrite(&row->discount, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_writeRow() write discount is error!");
    if(fwrite(&row->rateOfVAT, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_writeRow() write rateOfVAT is error!");
    /*provided_DocumentRow_writeRow(row, file);*/
}

/** Read a row from a file
 * @param file the opened file
 * @return a new row created on the heap filled with the data
 */
DocumentRow * DocumentRow_readRow(FILE * file) {
    DocumentRow *newRow;
    newRow = (DocumentRow *)malloc(sizeof(DocumentRow));
    if(newRow == NULL)
        fatalError("DocumentRow_readRow() malloc is error!!");

    newRow->code = readString(file);
    newRow->designation = readString(file);
    if(fread(&newRow->quantity, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_readRow() read quantity is error!");
    newRow->unity = readString(file);
    if(fread(&newRow->basePrice, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_readRow() read basePrice is error!");
    if(fread(&newRow->sellingPrice, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_readRow() read sellingPrice is error!");
    if(fread(&newRow->discount, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_readRow() read discount is error!");
    if(fread(&newRow->rateOfVAT, sizeof(double), 1, file) != 1 )
        fatalError("DocumentRow_readRow() read rateOfVAT is error!");
    return newRow;
    /*return provided_DocumentRow_readRow(file);*/
}
