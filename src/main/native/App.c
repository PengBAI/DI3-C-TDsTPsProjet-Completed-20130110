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
 * $Id: App.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <App.h>
#include <MainWindow.h>

#include <BridgeUtil.h>
#include <base/Registry.h>

#include <MyStringUnit.h>
#include <OperatorTableUnit.h>
#include <EncryptDecryptUnit.h>
#include <CatalogRecordUnit.h>
#include <CatalogDBUnit.h>
#include <CustomerRecordUnit.h>
#include <CustomerDBUnit.h>
#include <DocumentUtilUnit.h>
#include <PrintFormatUnit.h>
#include <DictionaryUnit.h>
#include <DocumentRowListUnit.h>
#include <DocumentUnit.h>

void App_init(int * argc, char * *argv[]) {
    brigeSetup();

    /* Initialise GTK+ passing to it all command line arguments  */
    gtk_init(argc, argv);

    brigeSetup();

    printf("Running preliminary unit test...\n");
    test_MyString();
    test_EncryptDecrypt();
    test_OperatorTable();
    test_CatalogRecord();
    test_CatalogDB();
    test_CustomerRecord();
    test_CustomerDB();
    test_DocumentUtil();
    test_DocumentRowList();
    test_Document();
    test_PrintFormat();
    test_Dictionary();
    printf("Great ! Unit tests passed !\n");

    /* Create and display the main window */
    gtk_widget_show(MainWindow_create());
}

void App_run(void) {
    /* run the GTK+ main loop */
    gtk_main();
}

void App_finalize(void) {
    /** Dump provided function usage */
    Registry_dumpUsage();

    Registry_finalize();
}
