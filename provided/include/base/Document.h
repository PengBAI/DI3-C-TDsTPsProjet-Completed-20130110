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
 * $Id: Document.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BASE_DOCUMENT_H
#define FACTURATION_BASE_DOCUMENT_H

#include <base/Config.h>
#include <base/CustomerRecord.h>
#include <base/DocumentRowList.h>

/** @defgroup Documents Document management */

/** @defgroup Document Documents
 * @ingroup Documents
 * @{
 */

/** Enumeration defining the type of a document */
typedef enum {
    QUOTATION /**< It's a quotation */,
    BILL/**< It's a bill */
} TypeDocument;

/** Structure representing a document */
typedef struct {
    CustomerRecord customer /** The customer */;
    char * editDate /** The last edit data */;
    char * expiryDate /** The peremption date */;
    char * docNumber /** The document number */;
    char * object /** The object of the document */;
    char * operator /** The last operator */;
    DocumentRow * rows /** The rows */;
    TypeDocument typeDocument /** The type of document */;
} Document;

/** @} */

#endif
