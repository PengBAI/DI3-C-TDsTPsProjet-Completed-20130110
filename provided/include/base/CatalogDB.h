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
 * $Id: CatalogDB.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BASE_CATALOGDB_H
#define FACTURATION_BASE_CATALOGDB_H

#include <base/Config.h>
#include <base/CatalogRecord.h>

/**
 * @defgroup CatalogDB Catalog database
 * @ingroup Product
 * @{
 */

/** The catalog file name */
extern const char * CATALOGDB_FILENAME;

/** The structure which represents an opened catalog database */
typedef struct _CatalogDB {
    FILE * file; /**< The FILE pointer for the associated file */
    int recordCount; /**< The number of record in the database */
} CatalogDB;

/** @} */

#endif
