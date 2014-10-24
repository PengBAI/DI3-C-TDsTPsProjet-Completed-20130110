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
 * $Id: DocumentUnit.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Document.h>
#include <UnitTest.h>
#include <DocumentRowList.h>

void test_Document(void) {
    Document document;

    Document_init(&document);

    DocumentRowList_pushBack(&document.rows, DocumentRow_create());
    DocumentRowList_pushBack(&document.rows, DocumentRow_create());
    DocumentRowList_pushBack(&document.rows, DocumentRow_create());
    DocumentRowList_pushBack(&document.rows, DocumentRow_create());
    DocumentRowList_pushBack(&document.rows, DocumentRow_create());

    Document_saveToFile(&document, "../document-unittest.db");
    Document_finalize(&document);

    Document_init(&document);
    ASSERT_EQUAL(DocumentRowList_getRowCount(document.rows), 0);
    Document_loadFromFile(&document, "../document-unittest.db");
    ASSERT_EQUAL(DocumentRowList_getRowCount(document.rows), 5);
    Document_finalize(&document);
}
