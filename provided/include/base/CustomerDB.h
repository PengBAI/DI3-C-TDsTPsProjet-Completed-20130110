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
 * $Id: CustomerDB.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BASE_CUSTOMERDB_H
#define FACTURATION_BASE_CUSTOMERDB_H

#include <base/Config.h>
#include <base/CustomerRecord.h>

/** @defgroup CustomerDB Customer database
 * @ingroup Customers
 * @{
 */

/** The customer database file name */
extern const char * CUSTOMERDB_FILENAME;

/** The structure which represents an opened customer database */
typedef struct {
    FILE * file; /**< The FILE pointer for the associated file */
    int recordCount; /**< The number of record in the database */
} CustomerDB;

/** @} */

#endif
