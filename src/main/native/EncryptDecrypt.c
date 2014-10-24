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
 * $Id: EncryptDecrypt.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <EncryptDecrypt.h>
#include <provided/EncryptDecrypt.h>

void encrypt(const char * key, char * str) {
    int keyLenth = (int)stringLength(key);
    int i = 0;
    int j = 0;
    while(str[j] != '\0')
    {
        if(toUpperChar(str[j]) <= 'Z' && toUpperChar(str[j]) >= 'A')
        {
            str[j] = (char)((toUpperChar(str[j]) - 'A' + toUpperChar(key[i % keyLenth]) - 'A') % 26 + 'a');
            i++;
        }
        j++;
    }
    /*provided_encrypt(key,str);*/
}
void decrypt(const char * key, char * str) {
    int keyLenth = (int)stringLength(key);
    int i = 0;
    int j = 0;
    while(str[j] != '\0')
    {
        if(toUpperChar(str[j]) <= 'Z' && toUpperChar(str[j]) >= 'A')
        {
            str[j] = (char)((26 - toUpperChar(key[i % keyLenth]) + toUpperChar(str[j])) % 26 + 'a');
            i++;
        }
        j++;
    }
    /*provided_decrypt(key,str);*/
}
