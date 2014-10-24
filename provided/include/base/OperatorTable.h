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
 * $Id: OperatorTable.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BASE_OPERATORTABLE_H
#define FACTURATION_BASE_OPERATORTABLE_H

#include <base/Config.h>

/** @defgroup Operators Operators */

/** @defgroup OperatorTable Operator database
 * @ingroup Operators
 * @{
 */

/** The operator database file name */
extern const char * OPERATORDB_FILENAME;

/** The maximal length in characters of the name of an operator */
#define OPERATORTABLE_MAXNAMESIZE 20
/** The maximal length in characters of the password of an operator */
#define OPERATORTABLE_MAXPASSWORDSIZE 20

/** The dynamic table of operators */
typedef struct {
    /** The number of operators in the table */
    int recordCount;
    /** The data about the operators. It's a 2D array of strings.
     * @note records[operatorId][0] is the name of the operatorId'th operator
     * @note records[operatorId][1] is the password of the operatorId'th operator
     */
    char *** records;
} OperatorTable;

/** @} */

#endif
