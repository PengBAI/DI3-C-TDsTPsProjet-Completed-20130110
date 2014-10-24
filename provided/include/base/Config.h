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
 * $Id: Config.h 293 2011-10-02 15:05:44Z sebtic $
 */

#ifndef FACTURATION_BASE_CONFIG_H
#define FACTURATION_BASE_CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
/** Mark a parameter name as beeing unused to suppress compiler warnings.
 * @param name the name of the parameter.
 *
 * @remarks You only need to surround the parameter name with the macro.
 * @code
 * void functionName( int usedParam, double UNUSED(unusedParam) ) {
 * ...
 * }
 * @endcode
 */
# define UNUSED(name) name
#endif

# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif

/** Function which displays a message and halt the debugger before terminating the program
 * @param message the message to display
 * @param line the line from which the function was called
 * @param file the file from which the function was called
 */
void debugFatalError(const char * message, long line, const char * file);

/**
 * Function which displays a message before terminating the program
 * @param message the message to display
 * @note While debugging, it simplifies the debugging by halting the debugger
 * before the application is terminated when the fatalerror() function is called.
 */
#define fatalError(message) debugFatalError(message, __LINE__, __FILE__)

#include <base/MyString.h>

/* Allow the inclusion of GTK+ by ignoring an annoying warning due to GTK+ fuzziness */
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#include <gtk/gtk.h>
#pragma GCC diagnostic error "-Wsign-conversion"
#pragma GCC diagnostic error "-Wstrict-prototypes"

/** First name and last name of the students. */
extern const char * STUDENT_NAMES;
/** The current school years */
extern const char * STUDENT_YEARS;
/** The group of the students */
extern const char * STUDENT_GROUP;

/**
 * Compute the maximal value of the two parameters
 * @param x the first parameter
 * @param y the second parameter
 */
#define MAXVALUE(x, y) (((x)>(y))?(x):(y))

#endif
