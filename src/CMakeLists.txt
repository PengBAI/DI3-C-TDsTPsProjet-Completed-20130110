cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

PROJECT(facturation)

if( NOT WIN32 )
  set( main_link_flags "${main_link_flags} -ldl" )
endif()

set( CMAKE_MODULE_PATH ${PROJECT_BINARY_DIR}/../src/cmake )

set( main_sources_aux ./main/include/Config.h
./main/include/Quotation.h
./main/include/EncryptDecryptUnit.h
./main/include/Dictionary.h
./main/include/Operator.h
./main/include/CatalogDBUnit.h
./main/include/DocumentUtil.h
./main/include/DocumentUtilUnit.h
./main/include/Bill.h
./main/include/Customer.h
./main/include/MyStringUnit.h
./main/include/OperatorTable.h
./main/include/CustomerRecord.h
./main/include/DocumentUnit.h
./main/include/DocumentRowList.h
./main/include/Print.h
./main/include/DocumentRowListUnit.h
./main/include/CatalogRecordUnit.h
./main/include/PrintFormatUnit.h
./main/include/GtkCustomerModel.h
./main/include/DictionaryUnit.h
./main/include/CatalogRecord.h
./main/include/BridgeUtil.h
./main/include/Document.h
./main/include/CustomerDBUnit.h
./main/include/MainWindow.h
./main/include/MyString.h
./main/include/CatalogDB.h
./main/include/UnitTest.h
./main/include/GtkCatalogModel.h
./main/include/Catalog.h
./main/include/OperatorTableUnit.h
./main/include/CustomerRecordUnit.h
./main/include/CustomerDB.h
./main/include/PrintFormat.h
./main/include/EncryptDecrypt.h
./main/include/DocumentEditor.h
./main/include/App.h
../provided/include/bridge/Dictionary.h
../provided/include/bridge/DocumentUtil.h
../provided/include/bridge/OperatorTable.h
../provided/include/bridge/CustomerRecord.h
../provided/include/bridge/DocumentRowList.h
../provided/include/bridge/CatalogRecord.h
../provided/include/bridge/Document.h
../provided/include/bridge/MyString.h
../provided/include/bridge/CatalogDB.h
../provided/include/bridge/CustomerDB.h
../provided/include/bridge/PrintFormat.h
../provided/include/bridge/EncryptDecrypt.h
../provided/include/base/Config.h
../provided/include/base/Dictionary.h
../provided/include/base/Registry.h
../provided/include/base/DocumentUtil.h
../provided/include/base/OperatorTable.h
../provided/include/base/CustomerRecord.h
../provided/include/base/DocumentRowList.h
../provided/include/base/CatalogRecord.h
../provided/include/base/Document.h
../provided/include/base/MyString.h
../provided/include/base/CatalogDB.h
../provided/include/base/CustomerDB.h
../provided/include/base/PrintFormat.h
../provided/include/base/EncryptDecrypt.h
../provided/include/provided/Dictionary.h
../provided/include/provided/DocumentUtil.h
../provided/include/provided/OperatorTable.h
../provided/include/provided/CustomerRecord.h
../provided/include/provided/DocumentRowList.h
../provided/include/provided/CatalogRecord.h
../provided/include/provided/Document.h
../provided/include/provided/MyString.h
../provided/include/provided/CatalogDB.h
../provided/include/provided/CustomerDB.h
../provided/include/provided/PrintFormat.h
../provided/include/provided/EncryptDecrypt.h
)




INCLUDE( ${CMAKE_MODULE_PATH}/configure.cmake )
INCLUDE( ${CMAKE_MODULE_PATH}/configure-project-main.cmake )
INCLUDE( ${CMAKE_MODULE_PATH}/configure-project-test.cmake )
INCLUDE( ${CMAKE_MODULE_PATH}/configure-compiler-gcc.cmake )
INCLUDE( ${CMAKE_MODULE_PATH}/configure-gtk2.cmake )
INCLUDE( ${CMAKE_MODULE_PATH}/configure-provided.cmake )
INCLUDE( ${CMAKE_MODULE_PATH}/project-main.cmake )
INCLUDE( ${CMAKE_MODULE_PATH}/project-test.cmake )

