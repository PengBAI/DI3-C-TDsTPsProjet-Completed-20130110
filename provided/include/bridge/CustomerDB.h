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

#ifndef FACTURATION_BRIDGE_CUSTOMERDB_H
#define FACTURATION_BRIDGE_CUSTOMERDB_H

#include <base/CustomerDB.h>

/** @defgroup ProvidedCustomerDB Provided functions
 * @ingroup CustomerDB
 * @{
 */

/** Create a database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 * @relates CustomerDB
 */
extern CustomerDB * (*bridge_CustomerDB_create)(const char * filename);

/** Open an existing database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 * @relates CustomerDB
 */
extern CustomerDB * (*bridge_CustomerDB_open)(const char * filename);

/** Open if exists or create otherwise a database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 * @relates CustomerDB
 */
extern CustomerDB * (*bridge_CustomerDB_openOrCreate)(const char * filename);

/** Flush cached data, close a database and free the structure representing the opened database
 * @param customerDB a pointer on a CustomerDB representing the opened database
 * @relates CustomerDB
 */
extern void (*bridge_CustomerDB_close)(CustomerDB * customerDB);

/** Get the number of records of the database
 * @param customerDB the database
 * @return the number of records
 * @relates CustomerDB
 */
extern int (*bridge_CustomerDB_getRecordCount)(CustomerDB * customerDB);

/** Append the specified record at the end of the database
 * @param customerDB the database
 * @param record the record
 * @relates CustomerDB
 */
extern void (*bridge_CustomerDB_appendRecord)(CustomerDB * customerDB, CustomerRecord *record);

/** Insert the specified record at the given position in the database
 * @param customerDB the database
 * @param recordIndex the insertion position
 * @param record the record
 * @relates CustomerDB
 */
extern void (*bridge_CustomerDB_insertRecord)(CustomerDB * customerDB, int recordIndex,
        CustomerRecord * record);

/** Remove a record at a given position from the database
 * @param customerDB the database
 * @param recordIndex the removal position
 * @relates CustomerDB
 */
extern void (*bridge_CustomerDB_removeRecord)(CustomerDB * customerDB, int recordIndex);

/** Read a record from the database
 * @param customerDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 * @relates CustomerDB
 */
extern void (*bridge_CustomerDB_readRecord)(CustomerDB * customerDB, int recordIndex,
        CustomerRecord * record);

/** Write a record from the database
 * @param customerDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 * @relates CustomerDB
 */
extern void (*bridge_CustomerDB_writeRecord)(CustomerDB * customerDB, int recordIndex,
        CustomerRecord * record);

/** @} */

#endif
