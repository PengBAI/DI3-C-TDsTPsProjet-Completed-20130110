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
 * $Id: Dictionary.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BASE_DICTIONARY_H
#define FACTURATION_BASE_DICTIONARY_H

#include <base/Config.h>

/** @defgroup Format Document formatting */

/** @defgroup Dictionary Dictionary based formatting functions
 * @ingroup Format
 * @{
 */

/** Enumeration defining the type of the doctionary entries */
typedef enum {
    UNDEFINED_ENTRY /* It's undefined */, NUMBER_ENTRY /** It's a number */, STRING_ENTRY
/** It's a string */
} DictionaryEntryType;

/** Structure representing an entry in the dictionary */
typedef struct {
    /** The type of entry */
    DictionaryEntryType type;
    /** The name of the entry */
    char * name;
    /** The union which store the value of the entry */
    union {
        /** The value of the entry when it's a string */
        char * stringValue;
        /** The value of the entry when it's a real number */
        double numberValue;
    } value;
} DictionaryEntry;

/** Structure representing a dictionary */
typedef struct _Dictionary {
    /** The number of entries of the dictionary */
    int count;
    /** The table of entries */
    DictionaryEntry * entries;
} Dictionary;

/** @} */

#endif
