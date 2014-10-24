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
 * $Id: CatalogDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogDB.h>
#include <provided/CatalogDB.h>
#include <CatalogRecord.h>

/** The catalog file name */
const char * CATALOGDB_FILENAME = "../Catalog.db";

/** Create a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * CatalogDB_create(const char * filename) {
    CatalogDB *newctl;
    newctl = (CatalogDB *)malloc(sizeof(CatalogDB));
    if(newctl == NULL)
        fatalError("creat a new catalog is error!");
	if((newctl->file = fopen(filename, "wb+")) == NULL)
	{
		free(newctl);
        return NULL;
	}
	newctl->recordCount = 0;
	if(fwrite(&newctl->recordCount, sizeof(int), 1, newctl->file) != 1)
	{
	    fclose(newctl->file);
		free(newctl);
		return NULL;
	}
	return newctl;
    /*return provided_CatalogDB_create(filename);*/
}

/** Open an existing database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * CatalogDB_open(const char * filename) {
    CatalogDB *openDB;
    openDB = (CatalogDB *)malloc(sizeof(CatalogDB));
    if(openDB == NULL)
        fatalError("open a database is error!");
    if((openDB->file = fopen(filename, "rb+")) == NULL)
    {
        free(openDB);
        return NULL;
    }
	if(fread(&openDB->recordCount, sizeof(int), 1, openDB->file) == 0)
	{
	    fclose(openDB->file);
		free(openDB);
		return NULL;
	}
    return openDB;
    /*return provided_CatalogDB_open(filename);*/
}

/** Open if exists or create otherwise a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * CatalogDB_openOrCreate(const char * filename) {
    CatalogDB *newCata;
    newCata = CatalogDB_open(filename);
    if(newCata == NULL)
    {
        return CatalogDB_create(filename);
    }
    return newCata;
    /*return provided_CatalogDB_openOrCreate(filename);*/
}

/** Flush cached data, close a database and free the structure representing the opened database
 * @param catalogDB a pointer on a CatalogDB representing the opened database
 */
void CatalogDB_close(CatalogDB * catalogDB) {
    rewind(catalogDB->file);
    if(fwrite(&catalogDB->recordCount, sizeof(int), 1, catalogDB->file) != 1)
        fatalError("CatalogDB_close()fwrite is error!");
    fclose(catalogDB->file);
    free(catalogDB);
    catalogDB = NULL;
    /*provided_CatalogDB_close(catalogDB);*/
}

/** Get the number of records of the database
 * @param catalogDB the database
 * @return the number of records
 */
int CatalogDB_getRecordCount(CatalogDB * catalogDB) {
    return catalogDB->recordCount;
    /*return provided_CatalogDB_getRecordCount(catalogDB);*/
}

/** Create a new string on the heap containing the value of the specified field for the specified record of a database
 * @param catalogDB the database
 * @param recordIndex the record index
 * @param field the field to query
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogDB_getFieldValueAsString(CatalogDB * catalogDB, int recordIndex, int field) {
    char * content = NULL;
    if (catalogDB != NULL) {
        CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(field);
        CatalogRecord record;
        CatalogRecord_init(&record);
        CatalogDB_readRecord(catalogDB, recordIndex, &record);
        content = properties.getValue(&record);
        CatalogRecord_finalize(&record);
    }
    return content;
}

/** Append the specified record at the end of the database
 * @param catalogDB the database
 * @param record the record
 */
void CatalogDB_appendRecord(CatalogDB * catalogDB, CatalogRecord *record) {
    CatalogDB_writeRecord(catalogDB,catalogDB->recordCount,record);
    /*provided_CatalogDB_appendRecord(catalogDB, record);*/
}

/** Insert the specified record at the given position in the database
 * @param catalogDB the database
 * @param recordIndex the insertion position
 * @param record the record
 */
void CatalogDB_insertRecord(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    int i = catalogDB->recordCount;
    CatalogRecord newRecord;
    CatalogRecord_init(&newRecord);
    while(i > recordIndex)
    {

        CatalogDB_readRecord(catalogDB, i - 1, &newRecord);
        CatalogDB_writeRecord(catalogDB, i, &newRecord);
        i--;
    }
    CatalogRecord_finalize(&newRecord);
    CatalogDB_writeRecord(catalogDB, recordIndex, record);
    /*provided_CatalogDB_insertRecord(catalogDB, recordIndex, record);*/
}

/** Remove a record at a given position from the database
 * @param catalogDB the database
 * @param recordIndex the removal position
 */
void CatalogDB_removeRecord(CatalogDB * catalogDB, int recordIndex) {
    CatalogRecord catalog;
    CatalogRecord_init(&catalog);
    while(recordIndex < catalogDB->recordCount - 1)
    {
        CatalogDB_readRecord(catalogDB, recordIndex + 1, &catalog);
        CatalogDB_writeRecord(catalogDB, recordIndex, &catalog);
        recordIndex++;
    }
    catalogDB->recordCount--;
    CatalogRecord_finalize(&catalog);
    /*provided_CatalogDB_removeRecord(catalogDB, recordIndex);*/
}

/** Read a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 */
void CatalogDB_readRecord(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    if(fseek(catalogDB->file, recordIndex * CATALOGRECORD_SIZE + (long int)sizeof(int), SEEK_SET) != 0)
        fatalError("CatalogDB_readRecord() fseek is error!");
    CatalogRecord_read(record, catalogDB->file);
    /*provided_CatalogDB_readRecord(catalogDB, recordIndex, record);*/
}

/** Write a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 */
void CatalogDB_writeRecord(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    if(fseek(catalogDB->file, recordIndex * CATALOGRECORD_SIZE + (long int)sizeof(int), SEEK_SET) != 0)
        fatalError("CatalogDB_writeRecord() fseek is error!");
    if(recordIndex == catalogDB->recordCount)
    {
        CatalogRecord_write(record,catalogDB->file);
        catalogDB->recordCount++;
    }
    else
    {
        CatalogRecord_write(record, catalogDB->file);
    }
    /*provided_CatalogDB_writeRecord(catalogDB, recordIndex, record);*/
}

