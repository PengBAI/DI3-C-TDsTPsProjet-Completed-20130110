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
 * A PARTICULARlder PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this source code. If not, see <http://www.gnu.org/licenses/>.
 *
 * $Id: main.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <App.h>

/** First name and last name of the students. */
const char * STUDENT_NAMES = "BAI Peng";
/** The current school years */
const char * STUDENT_YEARS = "2012-2013";
/** The group of the students */
const char * STUDENT_GROUP = "Groupe Mundus";

/** The main function
 * @param argc the number of arguments of the program
 * @param argv the arguments of the program
 */
int main(int argc, char *argv[]) {
    App_init(&argc, &argv);
    App_run();
    App_finalize();
    return 0;
}
