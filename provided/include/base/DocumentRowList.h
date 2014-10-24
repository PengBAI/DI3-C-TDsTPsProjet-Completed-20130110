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

#ifndef FACTURATION_BASE_DOCUMENTROWLIST_H
#define FACTURATION_BASE_DOCUMENTROWLIST_H

#include <base/Config.h>

/** @defgroup DocumentRowList List of rows of a document
 * @see Document
 * @ingroup Documents
 * @{
 */

/** Structure representing a row in a document (as a cell in a simple linked list */
typedef struct _DocumentRow {
    char * code /** The code */;
    char * designation /** The designation */;
    double quantity /** The quantity */;
    char * unity /** The unity */;
    double basePrice /** The base price */;
    double sellingPrice /** The selling price */;
    double discount /** The discount */;
    double rateOfVAT /** The rate of VAT */;
    struct _DocumentRow * next /** The pointer to the next row */;
} DocumentRow;

/** @} */

#endif
