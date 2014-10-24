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
 * $Id: DocumentUtil.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentUtil.h>
#include <provided/DocumentUtil.h>

/** Create a new string on the heap which represents the parameter as a number in basis 36.
 * @param id the number to convert
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * computeDocumentNumber(long id) {
    int heaplength = 0;
    char * strbas;
    long idcopy = id;
    int i;
    while(idcopy != 0)
    {
        idcopy = idcopy / 36;
        heaplength++;
    }
    if(id >= 0)
    {
        strbas = (char *)malloc((size_t)(heaplength + 1));
        if(strbas == NULL)
            fatalError("computeDocumentNumber()failure to creat a heap!");
        strbas[heaplength] = '\0';
        for(i = heaplength - 1; i >= 0; i--)
        {
            if(id % 36 > 9)
                strbas[i] = (char) (id % 36 - 10 + 'A');
            else
                strbas[i] = (char) (id % 36 + '0');
            id = id / 36;
        }
        return strbas;
    }
    else
    {
        id = -id;
        strbas = (char *)malloc((size_t)(heaplength + 2));
        if(strbas == NULL)
            fatalError("computeDocumentNumber()failure to creat a heap!");
        strbas[heaplength + 1] = '\0';
        strbas[0] = '-';
        for(i = heaplength; i > 0; i--)
        {
            if(id % 36 > 9)
                strbas[i] = (char) (id % 36 - 10 + 'A');
            else
                strbas[i] = (char) (id % 36 + '0');
            id = id / 36;
        }
        return strbas;
    }
    /*return provided_computeDocumentNumber(id);*/
}

/** Create a new string on the heap which represents the date in the format DD/MM/YYYY.
 * @param day the day
 * @param month the month
 * @param year the year
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * formatDate(int day, int month, int year) {
    char *date;
    date = (char *)malloc (11);
    if(date == NULL)
        fatalError("formatDate()failure to creat a heap for date!");
    sprintf(date, "%02d/%02d/%4d", day, month, year);
    return date;
    /*return provided_formatDate(day, month, year);*/
}


/** Write a string in a binary file
 * @param str the string
 * @param file the file
 */
void writeString(const char * str, FILE * file) {
    size_t strlength = stringLength(str);
    if(fwrite(&strlength, sizeof(size_t), 1, file) != 1)
        fatalError("writeString()failure to write!");
    if(strlength != 0)
    {
        if(fwrite(str, strlength, 1, file) != 1)
            fatalError("writeString()failure to write!");
    }
    /*provided_writeString(str,file);*/
}

/** Read a string from a binary file
 * @param file the file
 * @return a new string created on the heap which contains the read string
 * @see writeString()
 */
char * readString(FILE * file) {
    char * newstr;
    size_t length;
    if(fread(&length, sizeof(size_t), 1, file) != 1)
        fatalError("readString()read length of string is errer!");
    newstr = (char *)malloc(length + 1);
    if(newstr == NULL)
        fatalError("readString()creat a heap is error!");
    if(length != 0)
    {
        if(fread(newstr, length, 1, file) != 1)
            fatalError("readString()failure to read!");
    }
    newstr[length] = '\0';
    return newstr;
    /*return provided_readString(file);*/
}
