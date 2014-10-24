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
 * $Id: CustomerRecord.h 247 2010-09-10 10:23:07Z sebtic $
 */

#ifndef FACTURATION_CUSTOMERRECORD_H
#define FACTURATION_CUSTOMERRECORD_H

#include <Config.h>
#include <base/CustomerRecord.h>

/** @defgroup CustomerRecord Customer record
 * @ingroup Customers
 * @{
 */

/** Static function to set the name field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CustomerRecord_setValue_name(CustomerRecord * record, const char * value);

/** Static function to set the address field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CustomerRecord_setValue_address(CustomerRecord * record, const char * value);

/** Static function to set the postalCode field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CustomerRecord_setValue_postalCode(CustomerRecord * record, const char * value);

/** Static function to set the town field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void CustomerRecord_setValue_town(CustomerRecord * record, const char * value);

/** Static function which create a copy string on the head of the name field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CustomerRecord_getValue_name(CustomerRecord * record);

/** Static function which create a copy string on the head of the address field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CustomerRecord_getValue_address(CustomerRecord * record);

/** Static function which create a copy string on the head of the postalCode field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CustomerRecord_getValue_postalCode(CustomerRecord * record);

/** Static function which create a copy string on the head of the town field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CustomerRecord_getValue_town(CustomerRecord * record);

/** Initialize a record
 * @param[in] record a pointer to a record to initialize
 * @warning every initialized record must be finalized with CustomerRecord_finalize()
 * @relates CustomerRecord
 */
void CustomerRecord_init(CustomerRecord * record);
/** Get a copy of the properties of a field
 * @param field the identifier of the field
 * @return the properties
 * @see CustomerRecord_FieldIdentifier
 * @relates CustomerRecord
 */
CustomerRecord_FieldProperties
CustomerRecord_getFieldProperties(int field);

/** Finalize a record.
 * @param[in] record a pointer to a record to finalize
 * @relates CustomerRecord
 */
void CustomerRecord_finalize(CustomerRecord * record);

/** Edit a record
 * @param record a pointer to the record to edit
 * @return a non null value if the changes were validated, 0 otherwise
 * @relates CustomerRecord
 */
int CustomerRecord_edit(CustomerRecord * record);

/** Read a record from a file
 * @param record a pointer to an initialized record on which to store data
 * @param file the file from which the data are read
 * @relates CustomerRecord
 */
void CustomerRecord_read(CustomerRecord * record, FILE * file);

/** Write a record to a file
 * @param record a pointer to a record
 * @param file the file to which the data are written
 * @relates CustomerRecord
 */
void CustomerRecord_write(CustomerRecord * record, FILE * file);

/** @} */

#endif
