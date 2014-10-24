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
 * $Id: MyString.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BASE_MYSTRING_H
#define FACTURATION_BASE_MYSTRING_H

#include <base/Config.h>

/** @defgroup String String utility functions
 * @{
 */
/* Replace the standard strcmp() function with our function */
#define strcmp compareString
/* Replace the standard strlen() function with our function */
#define strlen stringLength
/* Replace the standard strcpy() function with our function */
#define strcpy provided_dangerousStrCpy
/* Replace the standard strncpy() function with our function */
#define strncpy provided_dangerousStrNCpy
/* Replace the standard strdup() function with our function */
#define strdup duplicateString
/* Replace the standard strcasecmp() function with our function */
#define strcasecmp icaseCompareString
/* Replace the standard tolower() function with our function */
#define tolower toLowerChar
/* Replace the standard toupper() function with our function */
#define toupper toUpperChar
/* Replace the standard strcat() function with our function */
#define strcat provided_dangerousStrCat
/* Replace the standard strncat() function with our function */
#define strncat provided_dangerousStrNCat
/* Replace the standard index() function with our function */
#define index indexOfChar
/* Replace the standard strstr() function with our function */
#define strstr indexOfString

/** @} */

#endif
