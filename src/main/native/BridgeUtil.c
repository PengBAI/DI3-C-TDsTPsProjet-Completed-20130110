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
 * $Id: BridgeUtil.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <BridgeUtil.h>
#include <bridge/CatalogDB.h>
#include <bridge/CatalogRecord.h>
#include <bridge/CustomerDB.h>
#include <bridge/CustomerRecord.h>
#include <bridge/Dictionary.h>
#include <bridge/Document.h>
#include <bridge/DocumentRowList.h>
#include <bridge/DocumentUtil.h>
#include <bridge/EncryptDecrypt.h>
#include <bridge/MyString.h>
#include <bridge/OperatorTable.h>
#include <bridge/PrintFormat.h>

#include <CatalogDB.h>
#include <CatalogRecord.h>
#include <CustomerDB.h>
#include <CustomerRecord.h>
#include <Dictionary.h>
#include <Document.h>
#include <DocumentRowList.h>
#include <DocumentUtil.h>
#include <EncryptDecrypt.h>
#include <MyString.h>
#include <OperatorTable.h>
#include <PrintFormat.h>

void brigeSetup(void) {
    bridge_CatalogDB_create = CatalogDB_create;
    bridge_CatalogDB_open = CatalogDB_open;
    bridge_CatalogDB_openOrCreate = CatalogDB_openOrCreate;
    bridge_CatalogDB_close = CatalogDB_close;
    bridge_CatalogDB_getRecordCount = CatalogDB_getRecordCount;
    bridge_CatalogDB_appendRecord = CatalogDB_appendRecord;
    bridge_CatalogDB_insertRecord = CatalogDB_insertRecord;
    bridge_CatalogDB_removeRecord = CatalogDB_removeRecord;
    bridge_CatalogDB_readRecord = CatalogDB_readRecord;
    bridge_CatalogDB_writeRecord = CatalogDB_writeRecord;
    bridge_CatalogRecord_isValueValid_code = CatalogRecord_isValueValid_code;
    bridge_CatalogRecord_isValueValid_positiveNumber = CatalogRecord_isValueValid_positiveNumber;
    bridge_CatalogRecord_setValue_code = CatalogRecord_setValue_code;
    bridge_CatalogRecord_setValue_designation = CatalogRecord_setValue_designation;
    bridge_CatalogRecord_setValue_unity = CatalogRecord_setValue_unity;
    bridge_CatalogRecord_setValue_basePrice = CatalogRecord_setValue_basePrice;
    bridge_CatalogRecord_setValue_sellingPrice = CatalogRecord_setValue_sellingPrice;
    bridge_CatalogRecord_setValue_rateOfVAT = CatalogRecord_setValue_rateOfVAT;
    bridge_CatalogRecord_getValue_code = CatalogRecord_getValue_code;
    bridge_CatalogRecord_getValue_designation = CatalogRecord_getValue_designation;
    bridge_CatalogRecord_getValue_unity = CatalogRecord_getValue_unity;
    bridge_CatalogRecord_getValue_basePrice = CatalogRecord_getValue_basePrice;
    bridge_CatalogRecord_getValue_sellingPrice = CatalogRecord_getValue_sellingPrice;
    bridge_CatalogRecord_getValue_rateOfVAT = CatalogRecord_getValue_rateOfVAT;
    bridge_CatalogRecord_init = CatalogRecord_init;
    bridge_CatalogRecord_finalize = CatalogRecord_finalize;
    bridge_CatalogRecord_read = CatalogRecord_read;
    bridge_CatalogRecord_write = CatalogRecord_write;
    bridge_CustomerDB_create = CustomerDB_create;
    bridge_CustomerDB_open = CustomerDB_open;
    bridge_CustomerDB_openOrCreate = CustomerDB_openOrCreate;
    bridge_CustomerDB_close = CustomerDB_close;
    bridge_CustomerDB_getRecordCount = CustomerDB_getRecordCount;
    bridge_CustomerDB_appendRecord = CustomerDB_appendRecord;
    bridge_CustomerDB_insertRecord = CustomerDB_insertRecord;
    bridge_CustomerDB_removeRecord = CustomerDB_removeRecord;
    bridge_CustomerDB_readRecord = CustomerDB_readRecord;
    bridge_CustomerDB_writeRecord = CustomerDB_writeRecord;
    bridge_CustomerRecord_setValue_name = CustomerRecord_setValue_name;
    bridge_CustomerRecord_setValue_address = CustomerRecord_setValue_address;
    bridge_CustomerRecord_setValue_postalCode = CustomerRecord_setValue_postalCode;
    bridge_CustomerRecord_setValue_town = CustomerRecord_setValue_town;
    bridge_CustomerRecord_getValue_name = CustomerRecord_getValue_name;
    bridge_CustomerRecord_getValue_address = CustomerRecord_getValue_address;
    bridge_CustomerRecord_getValue_postalCode = CustomerRecord_getValue_postalCode;
    bridge_CustomerRecord_getValue_town = CustomerRecord_getValue_town;
    bridge_CustomerRecord_init = CustomerRecord_init;
    bridge_CustomerRecord_finalize = CustomerRecord_finalize;
    bridge_CustomerRecord_read = CustomerRecord_read;
    bridge_CustomerRecord_write = CustomerRecord_write;
    bridge_Dictionary_create = Dictionary_create;
    bridge_Dictionary_destroy = Dictionary_destroy;
    bridge_Dictionary_getEntry = Dictionary_getEntry;
    bridge_Dictionary_setStringEntry = Dictionary_setStringEntry;
    bridge_Dictionary_setNumberEntry = Dictionary_setNumberEntry;
    bridge_Dictionary_format = Dictionary_format;
    bridge_Document_init = Document_init;
    bridge_Document_finalize = Document_finalize;
    bridge_Document_saveToFile = Document_saveToFile;
    bridge_Document_loadFromFile = Document_loadFromFile;
    bridge_DocumentRow_init = DocumentRow_init;
    bridge_DocumentRow_finalize = DocumentRow_finalize;
    bridge_DocumentRow_create = DocumentRow_create;
    bridge_DocumentRow_destroy = DocumentRow_destroy;
    bridge_DocumentRowList_init = DocumentRowList_init;
    bridge_DocumentRowList_finalize = DocumentRowList_finalize;
    bridge_DocumentRowList_get = DocumentRowList_get;
    bridge_DocumentRowList_getRowCount = DocumentRowList_getRowCount;
    bridge_DocumentRowList_pushBack = DocumentRowList_pushBack;
    bridge_DocumentRowList_insertBefore = DocumentRowList_insertBefore;
    bridge_DocumentRowList_insertAfter = DocumentRowList_insertAfter;
    bridge_DocumentRowList_removeRow = DocumentRowList_removeRow;
    bridge_DocumentRow_writeRow = DocumentRow_writeRow;
    bridge_DocumentRow_readRow = DocumentRow_readRow;
    bridge_computeDocumentNumber = computeDocumentNumber;
    bridge_formatDate = formatDate;
    bridge_writeString = writeString;
    bridge_readString = readString;
    bridge_encrypt = encrypt;
    bridge_decrypt = decrypt;
    bridge_stringLength = stringLength;
    bridge_compareString = compareString;
    bridge_icaseCompareString = icaseCompareString;
    bridge_copyString = copyString;
    bridge_copyStringWithLength = copyStringWithLength;
    bridge_duplicateString = duplicateString;
    bridge_icaseStartWith = icaseStartWith;
    bridge_icaseEndWith = icaseEndWith;
    bridge_concatenateString = concatenateString;
    bridge_toLowerChar = toLowerChar;
    bridge_toUpperChar = toUpperChar;
    bridge_makeUpperCaseString = makeUpperCaseString;
    bridge_makeLowerCaseString = makeLowerCaseString;
    bridge_indexOfChar = indexOfChar;
    bridge_indexOfString = indexOfString;
    bridge_subString = subString;
    bridge_insertString = insertString;
    bridge_OperatorTable_create = OperatorTable_create;
    bridge_OperatorTable_destroy = OperatorTable_destroy;
    bridge_OperatorTable_loadFromFile = OperatorTable_loadFromFile;
    bridge_OperatorTable_saveToFile = OperatorTable_saveToFile;
    bridge_OperatorTable_getRecordCount = OperatorTable_getRecordCount;
    bridge_OperatorTable_getName = OperatorTable_getName;
    bridge_OperatorTable_getPassword = OperatorTable_getPassword;
    bridge_OperatorTable_findOperator = OperatorTable_findOperator;
    bridge_OperatorTable_setOperator = OperatorTable_setOperator;
    bridge_OperatorTable_removeRecord = OperatorTable_removeRecord;
    bridge_PrintFormat_init = PrintFormat_init;
    bridge_PrintFormat_finalize = PrintFormat_finalize;
    bridge_PrintFormat_loadFromFile = PrintFormat_loadFromFile;
}
