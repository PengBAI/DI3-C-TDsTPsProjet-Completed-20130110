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
 * $Id: UnitTest.h 247 2010-09-10 10:23:07Z sebtic $
 */

#ifndef FACTURATION_UNITTEST_H
#define FACTURATION_UNITTEST_H

#include <Config.h>

#define ASSERT( cond )     do { \
                                if (!(cond)) { \
                                    fprintf(stderr, "Assertion %s failed in %s at line %d for function %s\n", #cond, __FILE__, (int)__LINE__, __func__ ); \
                                    fatalError("Assertion failed"); \
                                } \
                           } while (0)

#define ASSERT_EQUAL( x, y ) ASSERT( ((x)==(y)) )

#define ASSERT_NOT_EQUAL( x, y ) ASSERT( ((x)!=(y)) )

#define ASSERT_EQUAL_STRING( x, y ) ASSERT( (strcmp((x),(y)) == 0) )

#define ASSERT_EQUAL_DOUBLE( x, y ) ASSERT( fabs(x-y) < 0.0001 )

#endif
