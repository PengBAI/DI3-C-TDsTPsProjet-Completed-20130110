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
 * $Id: CustomerDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerDB.h>
#include <provided/CustomerDB.h>
#include <CustomerRecord.h>

/** The customer file name */
const char * CUSTOMERDB_FILENAME = "../Customer.db";

/** Create a database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 */
CustomerDB * CustomerDB_create(const char * filename) {
	CustomerDB *creatDB;
	creatDB = (CustomerDB *)malloc(sizeof(CustomerDB));
	if(creatDB == NULL)
		fatalError("CustomerDB_create()creat a new customerDB is error!");
	if((creatDB->file = fopen(filename, "wb+")) == NULL)
	{
		free(creatDB);
        return NULL;
	}
	creatDB->recordCount = 0;
	if(fwrite(&creatDB->recordCount, sizeof(int), 1, creatDB->file) != 1)
	{
	    fclose(creatDB->file);
		free(creatDB);
		return NULL;
	}
	fflush(creatDB->file);
	return creatDB;
    /*return provided_CustomerDB_create(filename);*/
}

/** Open an existing database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 */
CustomerDB * CustomerDB_open(const char * filename) {
    CustomerDB *openDB;
    openDB = (CustomerDB *)malloc(sizeof(CustomerDB));
    if(openDB == NULL)
        fatalError("CustomerDB_open()open a database is error!");
    if((openDB->file = fopen(filename, "rb+")) == NULL)
    {
        free(openDB);
        return NULL;
    }
	if(fread(&openDB->recordCount, sizeof(int), 1, openDB->file) != 1)
	{
	    fclose(openDB->file);
		free(openDB);
		return NULL;
	}
    return openDB;
    /*return provided_CustomerDB_open(filename);*/
}

/** Open if exists or create otherwise a database of customers
 * @param filename the file name of the database
 * @return a pointer on a CustomerDB representing the opened database, NULL otherwise
 */
CustomerDB * CustomerDB_openOrCreate(const char * filename) {
    CustomerDB *newCustomer;
    newCustomer = CustomerDB_open(filename);
    if(newCustomer == NULL)
    {
        return CustomerDB_create(filename);
    }
    return newCustomer;
    /*return provided_CustomerDB_openOrCreate(filename);*/
}

/** Flush cached data, close a database and free the structure representing the opened database
 * @param customerDB a pointer on a CustomerDB representing the opened database
 */
void CustomerDB_close(CustomerDB * customerDB) {
    rewind(customerDB->file);
    if(fwrite(&customerDB->recordCount, sizeof(int), 1, customerDB->file) != 1)
        fatalError("CustomerDB_close()fwrite is error!");
    fclose(customerDB->file);
    free(customerDB);
    customerDB = NULL;
    /*provided_CustomerDB_close(customerDB);*/
}

/** Get the number of records of the database
 * @param customerDB the database
 * @return the number of records
 */
int CustomerDB_getRecordCount(CustomerDB * customerDB) {
    return customerDB->recordCount;
    /*return provided_CustomerDB_getRecordCount(customerDB);*/
}

/** Create a new string on the heap containing the value of the specified field for the specified record of a database
 * @param customerDB the database
 * @param recordIndex the record index
 * @param field the field to query
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CustomerDB_getFieldValueAsString(CustomerDB * customerDB, int recordIndex, int field) {
    char * content = NULL;
    if (customerDB != NULL) {
        CustomerRecord_FieldProperties properties = CustomerRecord_getFieldProperties(field);
        CustomerRecord record;
        CustomerRecord_init(&record);
        CustomerDB_readRecord(customerDB, recordIndex, &record);
        content = properties.getValue(&record);
        CustomerRecord_finalize(&record);
    }
    return content;
}

/** Append the specified record at the end of the database
 * @param customerDB the database
 * @param record the record
 */
void CustomerDB_appendRecord(CustomerDB * customerDB, CustomerRecord *record) {
    CustomerDB_writeRecord(customerDB, customerDB->recordCount, record);
    /*provided_CustomerDB_appendRecord(customerDB, record);*/
}

/** Insert the specified record at the given position in the database
 * @param customerDB the database
 * @param recordIndex the insertion position
 * @param record the record
 */
void CustomerDB_insertRecord(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    int i = customerDB->recordCount;
    CustomerRecord newRecord;
    CustomerRecord_init(&newRecord);
    while(i > recordIndex)
    {

        CustomerDB_readRecord(customerDB, i - 1, &newRecord);
        CustomerDB_writeRecord(customerDB, i, &newRecord);
        i--;
    }
    CustomerRecord_finalize(&newRecord);
    CustomerDB_writeRecord(customerDB, recordIndex, record);
    /*provided_CustomerDB_insertRecord(customerDB, recordIndex, record);*/
}

/** Remove a record at a given position from the database
 * @param customerDB the database
 * @param recordIndex the removal position
 */
void CustomerDB_removeRecord(CustomerDB * customerDB, int recordIndex) {
    CustomerRecord customer;
    CustomerRecord_init(&customer);
    while(recordIndex < customerDB->recordCount - 1)
    {
        CustomerDB_readRecord(customerDB, recordIndex + 1, &customer);
        CustomerDB_writeRecord(customerDB, recordIndex, &customer);
        recordIndex++;
    }
    customerDB->recordCount--;
    CustomerRecord_finalize(&customer);
    /*provided_CustomerDB_removeRecord(customerDB, recordIndex);*/
}

/** Read a record from the database
 * @param customerDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 */
void CustomerDB_readRecord(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    if(fseek(customerDB->file, recordIndex * CUSTOMERRECORD_SIZE + (long int)sizeof(int), SEEK_SET) != 0)
        fatalError("CustomerDB_readRecord() fseek is error!");
    CustomerRecord_read(record, customerDB->file);
    /*provided_CustomerDB_readRecord(customerDB, recordIndex, record);*/
}

/** Write a record from the database
 * @param customerDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 */
void CustomerDB_writeRecord(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    if(fseek(customerDB->file, recordIndex * CUSTOMERRECORD_SIZE + (long int)sizeof(int), SEEK_SET) != 0)
        fatalError("CustomerDB_writeRecord() fseek is error!");
    if(recordIndex == customerDB->recordCount)
    {
        CustomerRecord_write(record, customerDB->file);
        customerDB->recordCount++;
    }
    else
    {
        CustomerRecord_write(record, customerDB->file);
    }
    /*provided_CustomerDB_writeRecord(customerDB, recordIndex, record);*/
}
