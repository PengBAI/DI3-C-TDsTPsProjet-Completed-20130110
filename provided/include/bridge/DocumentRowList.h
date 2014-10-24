/**
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
 * $Id: DocumentRowList.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BRIDGE_DOCUMENTROWLIST_H
#define FACTURATION_BRIDGE_DOCUMENTROWLIST_H

#include <base/DocumentRowList.h>

/** @defgroup ProvidedDocumentRowList Provided functions
 * @ingroup DocumentRowList
 * @{
 */

/** Initialize a row
 * @param row the row
 * @warning an initialized row must be finalized by DocumentRow_finalize() to free all resources
 */
extern void (*bridge_DocumentRow_init)(DocumentRow * row);

/** Finalize a row
 * @param row the row
 * @warning document must have been initialized
 */
extern void (*bridge_DocumentRow_finalize)(DocumentRow * row);

/** Create a new row on the heap and initialize it
 * @return the new row
 */
extern DocumentRow * (*bridge_DocumentRow_create)(void);

/** Finalize and destroy a row previously created on the heap
 * @param row the row
 */
extern void (*bridge_DocumentRow_destroy)(DocumentRow * row);

/** Initialize a list of rows
 * @param list the address of the pointer on the first cell of the list
 */
extern void (*bridge_DocumentRowList_init)(DocumentRow ** list);

/** Finalize a list of rows
 * @param list the address of the pointer on the first cell of the list
 * @note Each row of the list are destroyer using DocumentRow_destroy()
 */
extern void (*bridge_DocumentRowList_finalize)(DocumentRow ** list);

/** Get a pointer on the rowIndex-th row of the list
 * @param list the pointer on the first cell of the list
 * @param rowIndex the index of the requested row
 * @return a pointer on the rowIndex-th row of the list or NULL if the list contains less rows than the requested one
 */
extern DocumentRow * (*bridge_DocumentRowList_get)(DocumentRow * list, int rowIndex);

/**
 * Get the number of rows in the list
 * @param list the pointer on the first cell of the list
 */
extern int (*bridge_DocumentRowList_getRowCount)(DocumentRow * list);

/** Add a row at the end of the list
 * @param list the address of the pointer on the first cell of the list
 * @param row the row to add
 */
extern void (*bridge_DocumentRowList_pushBack)(DocumentRow ** list, DocumentRow * row);

/** Insert a row before a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
extern void (*bridge_DocumentRowList_insertBefore)(DocumentRow ** list, DocumentRow * position,
        DocumentRow * row);

/** Insert a row after a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
extern void (*bridge_DocumentRowList_insertAfter)(DocumentRow ** list, DocumentRow * position,
        DocumentRow * row);

/** Remove a row from the list
 * @param list the address of the pointer on the first cell of the list
 * @param position the row to remove
 */
extern void (*bridge_DocumentRowList_removeRow)(DocumentRow ** list, DocumentRow * position);

/** Write a row in a binary file
 * @param row the row
 * @param file the opened file
 */
extern void (*bridge_DocumentRow_writeRow)(DocumentRow * row, FILE * file);

/** Read a row from a file
 * @param file the opened file
 * @return a new row created on the heap filled with the data
 */
extern DocumentRow * (*bridge_DocumentRow_readRow)(FILE * file);

/** @} */

#endif
