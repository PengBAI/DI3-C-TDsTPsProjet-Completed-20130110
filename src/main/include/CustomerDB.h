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
 * $Id: CustomerDB.h 247 2010-09-10 10:23:07Z sebtic $
 */

#ifndef FACTURATION_CUSTOMERDB_H
#define FACTURATION_CUSTOMERDB_H

#include <Config.h>
#include <base/CustomerDB.h>

/** @defgroup CustomerDB Customer database
 * @ingroup Customers
 * @{
 */

/** Create a database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 * @relates CustomerDB
 */
CustomerDB * CustomerDB_create(const char * filename);
/** Open an existing database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 * @relates CustomerDB
 */
CustomerDB * CustomerDB_open(const char * filename);
/** Open if exists or create otherwise a database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 * @relates CustomerDB
 */
CustomerDB * CustomerDB_openOrCreate(const char * filename);

/** Flush cached data, close a database and free the structure representing the opened database
 * @param customerDB a pointer on a CustomerDB representing the opened database
 * @relates CustomerDB
 */
void CustomerDB_close(CustomerDB * customerDB);

/** Get the number of records of the database
 * @param customerDB the database
 * @return the number of records
 * @relates CustomerDB
 */
int CustomerDB_getRecordCount(CustomerDB * customerDB);

/** Create a new string on the heap containing the value of the specified field for the specified record of a database
 * @param customerDB the database
 * @param recordIndex the record index
 * @param field the field to query
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @relates CustomerDB
 */
char * CustomerDB_getFieldValueAsString(CustomerDB * customerDB, int recordIndex, int field);

/** Append the specified record at the end of the database
 * @param customerDB the database
 * @param record the record
 * @relates CustomerDB
 */
void CustomerDB_appendRecord(CustomerDB * customerDB, CustomerRecord *record);

/** Insert the specified record at the given position in the database
 * @param customerDB the database
 * @param recordIndex the insertion position
 * @param record the record
 * @relates CustomerDB
 */
void CustomerDB_insertRecord(CustomerDB * customerDB, int recordIndex, CustomerRecord * record);

/** Remove a record at a given position from the database
 * @param customerDB the database
 * @param recordIndex the removal position
 * @relates CustomerDB
 */
void CustomerDB_removeRecord(CustomerDB * customerDB, int recordIndex);

/** Read a record from the database
 * @param customerDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 * @relates CustomerDB
 */
void CustomerDB_readRecord(CustomerDB * customerDB, int recordIndex, CustomerRecord * record);

/** Write a record from the database
 * @param customerDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 * @relates CustomerDB
 */
void CustomerDB_writeRecord(CustomerDB * customerDB, int recordIndex, CustomerRecord * record);

/** @} */

#endif
