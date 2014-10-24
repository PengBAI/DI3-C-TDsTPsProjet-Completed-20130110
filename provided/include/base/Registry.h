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
 * $Id: Registry.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_REGISTRY_H
#define FACTURATION_REGISTRY_H

#include <base/Config.h>

/**
 * Declare the usage of a provided function
 * @param name the name of the function
 */
#define REGISTRY_USINGFUNCTION Registry_usingFunction(__func__, __FILE__)

/** Declare the usage of a provided function
 * @internal
 * @param name the name of the function
 */
void Registry_usingFunction(const char * name, const char * file);

/** Display the usage of the provided function */
void Registry_dumpUsage(void);

/** Finalize the registry */
void Registry_finalize(void);

#endif
