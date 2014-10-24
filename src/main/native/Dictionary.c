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
 * $Id: Dictionary.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Dictionary.h>
#include <provided/Dictionary.h>

/** Create an empty dictionary on the heap
 * @return a new dictionary
 * @warning the dictionary should be destroyed using Dictionary_destroy()
 */
Dictionary * Dictionary_create(void) {
    Dictionary *dict;
    dict = (Dictionary *)malloc(sizeof(Dictionary));
    if(dict == NULL)
        fatalError("Dictionary_create() malloc is error!");
    dict->count = 0;
    dict->entries = NULL;
    return dict;
    /*return provided_Dictionary_create();*/
}

/** Destroy a dictionary
 * @param dictionary the dictionary
 */
void Dictionary_destroy(Dictionary * dictionary) {
    int i;
    for(i = dictionary->count - 1; i >= 0; i--)
    {
        free(dictionary->entries[i].name);
        dictionary->entries[i].name = NULL;
        if(dictionary->entries[i].type == STRING_ENTRY)
        {
            free(dictionary->entries[i].value.stringValue);
            dictionary->entries[i].value.stringValue = NULL;
        }
    }
    free(dictionary->entries);
    dictionary->entries = NULL;
    free(dictionary);
    dictionary = NULL;
    /*provided_Dictionary_destroy(dictionary);*/
}

/** Get a pointer on the entry associated with the given entry name
 * @param dictionary the dictionary
 * @param name the name of the entry
 * @return a pointer on the entry or NULL if the entry was not found
 */
DictionaryEntry * Dictionary_getEntry(Dictionary * dictionary, const char * name) {
    int i;
    for(i = 0;i < dictionary->count;i++)
    {
        if(icaseCompareString(dictionary->entries[i].name, name) == 0)
            return dictionary->entries + i;
    }
    return NULL;
    /*return provided_Dictionary_getEntry(dictionary, name);*/
}

/** Define or change a dictionary entry as a string
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void Dictionary_setStringEntry(Dictionary * dictionary, const char * name, const char * value) {
    DictionaryEntry *result;
    result = Dictionary_getEntry(dictionary,name);
    if(result == NULL)
    {
        dictionary->entries = (DictionaryEntry *)realloc(dictionary->entries,(size_t)(dictionary->count + 1) * sizeof(DictionaryEntry));
        if(dictionary->entries == NULL)
            fatalError("Dictionary_setStringEntry() realloc is error!");
        dictionary->entries[dictionary->count].type = STRING_ENTRY;
        dictionary->entries[dictionary->count].name = duplicateString(name);
        dictionary->entries[dictionary->count].value.stringValue = duplicateString(value);
        dictionary->count++;
    }
    else
    {
        if(result->type == STRING_ENTRY)
            free(result->value.stringValue);
        result->type = STRING_ENTRY;
        result->value.stringValue = duplicateString(value);
    }
    /*provided_Dictionary_setStringEntry(dictionary, name, value);*/
}

/** Define or change a dictionary entry as a number
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void Dictionary_setNumberEntry(Dictionary * dictionary, const char * name, double value) {
    DictionaryEntry *result;
    result = Dictionary_getEntry(dictionary, name);
    if(result == NULL)
    {
        dictionary->entries = (DictionaryEntry *)realloc(dictionary->entries,(size_t)(dictionary->count + 1) * sizeof(DictionaryEntry));
        if(dictionary->entries == NULL)
            fatalError("Dictionary_setStringEntry() realloc is error!");
        dictionary->entries[dictionary->count].type = NUMBER_ENTRY;
        dictionary->entries[dictionary->count].name = duplicateString(name);
        dictionary->entries[dictionary->count].value.numberValue = value;
        dictionary->count++;
    }
    else
    {
        if(result->type == STRING_ENTRY)
            free(result->value.stringValue);
        result->type = NUMBER_ENTRY;
        result->value.numberValue = value;
    }
    /*provided_Dictionary_setNumberEntry(dictionary, name, value);*/
}

/** Create a new string on the heap which is the result of the formatting of format according to the dictionary content
 * @param dictionary the dictionary
 * @param format the string to format
 * @return a new string created on the heap
 * @warning the user is responsible for freeing the returned string
 */
char * Dictionary_format(Dictionary * dictionary, const char * format) {
    char *result, *tempLine, *newLine, *leformat, *spaces;
    char tempNumber[32];
    const char *tempFormat, *indexFormat;
    int isPrecision, isMin, isMax, isCaseU;
    int precision = 0, min = 0, max = 0, caseU = 0;
    size_t  len, spaceLenth;
    DictionaryEntry * entry;

    result = duplicateString("");
    tempFormat = format;
    do {
        isPrecision = 0;
        isMin = 0;
        isMax = 0;
        isCaseU = 0;
        indexFormat = indexOfChar(tempFormat, '%');

        /* there is not content to deal with */
        if(indexFormat == NULL)
        {
            newLine = result;
            result = concatenateString(result, tempFormat);
            free(newLine);
        }
        else
        {

            /* read the line before '%' */
            if(indexFormat != tempFormat)
            {
                tempLine = subString(tempFormat, indexFormat);
                newLine = result;
                result = concatenateString(result, tempLine);
                free(newLine);
                free(tempLine);
            }
            indexFormat++;
            tempFormat = indexFormat;

            /* the situation of "%%" */
            if(*tempFormat == '%')
            {
                newLine = result;
                result = concatenateString(result, "%");
                free(newLine);
                tempFormat++;
                indexFormat++;
            }
            else
            {
                /* read the entry from dictionary */
                while(*indexFormat != '%' && *indexFormat != '{')
                    indexFormat++;
                tempLine = subString(tempFormat, indexFormat);
                entry = Dictionary_getEntry(dictionary, tempLine);
                if(entry == NULL)
                {
                    while(*indexFormat != '%')
                        indexFormat++;
                    indexFormat++;
                    tempFormat = indexFormat;
                    free(tempLine);
                }
                else
                {
                    free(tempLine);

                    /* there is not the balise to deal with,only output the value */
                    if(*indexFormat == '%')
                    {
                        newLine = result;
                        if(entry->type == STRING_ENTRY)
                            result = concatenateString(result, entry->value.stringValue);
                        else
                        {
                            sprintf(tempNumber, "%f", entry->value.numberValue);
                            result = concatenateString(result, tempNumber);
                        }
                        free(newLine);
                        indexFormat++;
                        tempFormat = indexFormat;
                    }

                    /* there is the balise to deal with */
                    else if(*indexFormat == '{')
                    {
                        indexFormat++;

                        /* deal with the string */
                        if(entry->type == STRING_ENTRY)
                        {
                            while(*indexFormat != '%')
                            {
                                if(indexFormat[0] == 'm' && indexFormat[1] == 'i')
                                {
                                    tempFormat = (char *)(indexFormat + 4);
                                    indexFormat = (char *)(indexFormat + 4);
                                    while(*indexFormat != ',' && *indexFormat!= '}')
                                        indexFormat++;
                                    if(!isMin)
                                    {
                                        isMin = 1;
                                        tempLine = subString(tempFormat, indexFormat);
                                        min = atoi(tempLine);
                                        free(tempLine);
                                    }
                                }
                                else if(indexFormat[0] == 'm' && indexFormat[1] == 'a')
                                {
                                    tempFormat = (char *)(indexFormat + 4);
                                    indexFormat = (char *)(indexFormat + 4);
                                    while(*indexFormat != ',' && *indexFormat != '}')
                                        indexFormat++;
                                    if(!isMax)
                                    {
                                        isMax = 1;
                                        tempLine = subString(tempFormat, indexFormat);
                                        max = atoi(tempLine);
                                        free(tempLine);
                                    }
                                }
                                else if(indexFormat[0] == 'c')
                                {
                                    tempFormat = (char *)(indexFormat + 5);
                                    indexFormat = (char *)(indexFormat + 5);
                                    while(*indexFormat != ',' && *indexFormat != '}')
                                        indexFormat++;
                                    if(!isCaseU)
                                    {
                                        isCaseU = 1;
                                        caseU = (int) *tempFormat;
                                    }
                                }
                                indexFormat++;
                                tempFormat = indexFormat;
                            }
                            indexFormat++;
                            tempFormat++;
                            tempLine = duplicateString(entry->value.stringValue);
                            if(isCaseU)
                            {
                                if(caseU == 'U' || caseU == 'u')
                                    makeUpperCaseString(tempLine);
                                else
                                    makeLowerCaseString(tempLine);
                            }
                            if(isMax)
                            {
                                len = stringLength(tempLine);
                                if(len > (size_t)max)
                                    tempLine[max] = '\0';
                            }
                            newLine = result;
                            result = concatenateString(result, tempLine);
                            free(newLine);

                            if(isMin)
                            {
                                len = stringLength(tempLine);
                                if(len < (size_t)min)
                                {
                                    spaceLenth = (size_t)min - len;
                                    spaces =(char *)calloc((spaceLenth + 1),sizeof(char));
                                    while(spaceLenth--)
                                    {
                                        spaces[spaceLenth] = ' ';
                                    }
                                    spaces[(size_t)min - len] = '\0';
                                    newLine = result;
                                    result = concatenateString(result, spaces);
                                    free(newLine);
                                }
                            }
                            free(tempLine);
                        }

                        /* deal with the number */
                        else
                        {
                            while(*indexFormat != '%')
                            {
                                if(indexFormat[0] == 'm' && indexFormat[1] == 'i')
                                {
                                    tempFormat = (char *)(indexFormat + 4);
                                    indexFormat = (char *)(indexFormat + 4);
                                    while(*indexFormat != ',' && *indexFormat != '}')
                                        indexFormat++;
                                    if(!isMin)
                                    {
                                        isMin = 1;
                                        tempLine = subString(tempFormat, indexFormat);
                                        min = atoi(tempLine);
                                        free(tempLine);
                                    }
                                }
                                else if(indexFormat[0] == 'p')
                                {
                                    tempFormat = (char *)(indexFormat + 10);
                                    indexFormat = (char *)(indexFormat + 10);
                                    while(*indexFormat != ',' && *indexFormat != '}')
                                        indexFormat++;
                                    if(!isPrecision)
                                    {
                                        isPrecision = 1;
                                        tempLine = subString(tempFormat, indexFormat);
                                        precision = atoi(tempLine);
                                        free(tempLine);
                                    }
                                }
                                indexFormat++;
                                tempFormat = indexFormat;
                            }
                            indexFormat++;
                            tempFormat++;
                            if(isPrecision)
                            {
                                sprintf(tempNumber, "%d", precision);
                                leformat = duplicateString("%.");
                                newLine = leformat;
                                leformat = concatenateString(leformat, tempNumber);
                                free(newLine);
                                newLine = leformat;
                                leformat = concatenateString(leformat, "f");
                                free(newLine);
                                sprintf(tempNumber, leformat, entry->value.numberValue);
                                free(leformat);
                                tempLine = duplicateString(tempNumber);
                            }
                            if(isMin)
                            {
                                len = stringLength(tempLine);
                                if(len < (size_t)min)
                                {
                                    spaceLenth = (size_t)min - len;
                                    spaces =(char *)calloc((spaceLenth + 1), sizeof(char));
                                    while(spaceLenth--)
                                    {
                                        spaces[spaceLenth] = ' ';
                                    }
                                    spaces[(size_t)min - len] = '\0';
                                    newLine = result;
                                    result = concatenateString(result, spaces);
                                    free(newLine);
                                }
                            }
                            newLine = result;
                            result = concatenateString(result, tempLine);
                            free(newLine);
                            free(tempLine);
                        }
                    }
                }
            }
        }
    } while(indexFormat != NULL);
    return result;
    /*return provided_Dictionary_format(dictionary, format);*/
}
