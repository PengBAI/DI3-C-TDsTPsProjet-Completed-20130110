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
 * $Id: PrintFormat.h 247 2010-09-10 10:23:07Z sebtic $
 */

#ifndef FACTURATION_PRINTFORMAT_H
#define FACTURATION_PRINTFORMAT_H

#include <Config.h>
#include <base/PrintFormat.h>

/** @defgroup PrintFormat Print format model management
 * @ingroup Format
 * @{
 */

/** Initialize a print format
 * @param format a print format
 * @warning initialized print format should be finalized with PrintFormat_finalize()
 */
 void PrintFormat_init(PrintFormat * format);

/** Finalize a print format
 * @param format the print format
 */
 void PrintFormat_finalize(PrintFormat * format);

/** Load a print format from a file
 * @param format an initialized print format to fill
 * @param filename the file name
 */
 void PrintFormat_loadFromFile(PrintFormat * format, const char * filename);

/** Format a document according to a print format
 * @param document the document
 * @param printFormat the print format
 * @return a new string created on the heap containing the formatted document
 * @warning The user is responsible for freeing the memory
 */
 char * formatDocument(Document * document, PrintFormat * printFormat);

/** @} */

#endif
