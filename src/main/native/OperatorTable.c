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
 * $Id: OperatorTable.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <OperatorTable.h>
#include <provided/OperatorTable.h>
#include <EncryptDecrypt.h>

/**
 * Create an empty table of operators.
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * OperatorTable_create() {
    OperatorTable *newTable;
    newTable = (OperatorTable *)malloc(sizeof(OperatorTable));
    if( newTable == NULL )
        fatalError("OperatorTable_create()malloc is error!");
    newTable->records = NULL;
    newTable->recordCount = 0;
    return newTable;
    /*return provided_OperatorTable_create();*/
}

/** Free a table of operators.
 * @param table a pointer to the table to free
 * @relates OperatorTable
 */
void OperatorTable_destroy(OperatorTable * table) {
    int i;
    int recordCount = OperatorTable_getRecordCount(table);
    for(i = 0; i < recordCount; i++)
    {
        free(table->records[i][0]);
        table->records[i][0] = NULL;
        free(table->records[i][1]);
        table->records[i][1] = NULL;
        free(table->records[i]);
        table->records[i] = NULL;
    }
    free(table->records);
    table->records = NULL;
    free(table);
    table = NULL;
    /*provided_OperatorTable_destroy(table);*/
}

/** Load a table of operators from a file.
 * @param filename the file name
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * OperatorTable_loadFromFile(const char * filename) {
    FILE *file;
    int i, record;
    size_t nameLength, passwordLength;
    char name[OPERATORTABLE_MAXNAMESIZE + 1];
    char password[OPERATORTABLE_MAXPASSWORDSIZE + 1];
    OperatorTable *newTable;
    newTable = OperatorTable_create();

    file = fopen(filename, "rb");
    if(file != NULL)
    {
        if(fread(&record, sizeof(int), 1, file) != 1)
        {
            fclose(file);
            fatalError("OperatorTable_loadFromFile() read count is error!");
        }
        for(i = 0; i < record; i++)
        {
            if(fgets(name, OPERATORTABLE_MAXNAMESIZE + 1, file) == NULL)
            {
                fclose(file);
                fatalError("OperatorTable_loadFromFile() get name is error!");
            }
            nameLength = stringLength(name);
            name[nameLength - 1] = '\0';
            decrypt("polytech", name);
            if(fgets(password, OPERATORTABLE_MAXPASSWORDSIZE + 1, file) == NULL)
            {
                fclose(file);
                fatalError("OperatorTable_loadFromFile() get name is error!");
            }
            passwordLength = stringLength(password);
            password[passwordLength - 1] = '\0';
            decrypt("polytech", password);
            OperatorTable_setOperator(newTable, name, password);
        }
        fclose(file);
    }
    return newTable;
    /*return provided_OperatorTable_loadFromFile(filename);*/
}

/** Save a table of operators to a file.
 * @param table the table of operators
 * @param filename the file name
 * @relates OperatorTable
 */
void OperatorTable_saveToFile(OperatorTable * table, const char * filename) {
    FILE *file;
    int recordCount, i;
    char name[OPERATORTABLE_MAXNAMESIZE + 1];
    char password[OPERATORTABLE_MAXPASSWORDSIZE + 1];
    file = fopen(filename, "wb+");
    if(file == NULL)
        fatalError("OperatorTable_saveToFile() open file is error!");
    recordCount = table->recordCount;
    if(fwrite(&recordCount, sizeof(int), 1, file) != 1)
    {
        fclose(file);
        fatalError("OperatorTable_saveToFile() write count is error!");
    }
    for(i = 0; i < recordCount; i++)
    {
        copyStringWithLength(name, table->records[i][0], stringLength(table->records[i][0]) + 1);
        encrypt("polytech", name);
        fputs(name, file);
        fputc('\n', file);
        copyStringWithLength(password, table->records[i][1],stringLength(table->records[i][1]) + 1);
        encrypt("polytech", password);
        fputs(password, file);
        fputc('\n', file);
    }
    fclose(file);
    /*provided_OperatorTable_saveToFile(table, filename);*/
}

/** Get the number of records of a table of operators
 * @param table the table of operators
 * @return the number of records
 * @relates OperatorTable
 */
int OperatorTable_getRecordCount(OperatorTable * table) {
    return table->recordCount;
    /*return provided_OperatorTable_getRecordCount(table);*/
}

/** Get the name of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record number
 * @return the name of the operator
 * @relates OperatorTable
 */
const char * OperatorTable_getName(OperatorTable * table, int recordIndex) {
    if(recordIndex > table->recordCount || recordIndex < 0 )
        fatalError("record index is error!");
    return table->records[recordIndex][0];
    /*return provided_OperatorTable_getName(table, recordIndex);*/
}

/** Get the password of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record index
 * @return the paswword of the operator
 * @relates OperatorTable
 */
const char * OperatorTable_getPassword(OperatorTable * table, int recordIndex) {
    if(recordIndex > table->recordCount || recordIndex < 0 )
        fatalError("OperatorTable_getPassword()record index is error!");
    return table->records[recordIndex][1];
    /*return provided_OperatorTable_getPassword(table, recordIndex);*/
}

/** Get the record index associated with an operator name.
 * @param table the table of operators
 * @param name the name of the operator
 * @return the index of the operator or -1 if the operator is not in the table
 * @relates OperatorTable
 */
int OperatorTable_findOperator(OperatorTable * table, const char * name) {
    int i;
    for(i = 0; i < table->recordCount; i++)
    {
        if(icaseCompareString(table->records[i][0], name) == 0 )
		return i;
    }
    return -1;
    /*return provided_OperatorTable_findOperator(table, name);*/
}

/** Define or change the password of an operator
 * @param table the table of operators
 * @param name the name of the operator
 * @param password the password of the operator
 * @return the index of the operator in the table
 * @relates OperatorTable
 */
int OperatorTable_setOperator(OperatorTable * table, const char * name, const char * password) {
    int i;
    i = OperatorTable_findOperator(table,name);
    if( i != -1 )
    {
        free(table->records[i][1]);
        table->records[i][1] = duplicateString(password);
        return i;
    }
    else
    {
        size_t indexTable = (size_t)OperatorTable_getRecordCount(table);
        table->records = (char ***)realloc(table->records, sizeof(char **) * (indexTable + 1));
        if(table->records == NULL)
            fatalError("OperatorTable_setOperator()realloc is error!");
        table->records[indexTable] = (char **)malloc(sizeof(char *) * 2);
        if(table->records[indexTable] == NULL)
            fatalError("OperatorTable_setOperator()malloc is error!");
        table->records[indexTable][0] = duplicateString(name);
        table->records[indexTable][1] = duplicateString(password);
        table->recordCount++;
        return table->recordCount - 1;
    }
    /*return provided_OperatorTable_setOperator(table, name, password);*/
}

/** Remove an operator from the table.
 * @param table the table of operators
 * @param recordIndex the index of the record to remove
 * @relates OperatorTable
 */
void OperatorTable_removeRecord(OperatorTable * table, int recordIndex) {
    int i;
    if(table->recordCount == 1)
    {
        OperatorTable_destroy(table);
        table = OperatorTable_create();
    }
    else
    {
        for(i = recordIndex; i < table->recordCount - 1; i++)
        {
            free(table->records[i][0]);
            table->records[i][0] = duplicateString(table->records[i + 1][0]);
            free(table->records[i][1]);
            table->records[i][1] = duplicateString(table->records[i + 1][1]);
        }
        free(table->records[table->recordCount - 1][0]);
        free(table->records[table->recordCount - 1][1]);
        free(table->records[table->recordCount- 1]);
        table->recordCount--;
    }

    /*provided_OperatorTable_removeRecord(table, recordIndex);*/
}

