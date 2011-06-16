/*
 *
 *      Copyright Jun 18:04:36 CEST 2011 Eric Heim
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "zip_fgets.h"
#include <libzip/zip.h>
#include <string.h>
#include <android/log.h>


#define  LOG_TAG    "Utils.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

//! function that reads a new line or size -1 bytes into the buffer from a zipfile
size_t zip_fgets(char* buff, size_t size, zip_file* file)
{
    size_t rBytes = 0;
    unsigned int pos = 0;
    char tmpBuff[4096];

    do{

       rBytes = zip_fread(file,tmpBuff,1);

       if(rBytes != 0 && tmpBuff[0] != '\n'){
            buff[pos] = tmpBuff[0];
            pos++;
       }else{
            break;
       }

    }while(rBytes != 0 && pos < size - 1);

    buff[pos] = '\0';

    return strlen(buff);


}
