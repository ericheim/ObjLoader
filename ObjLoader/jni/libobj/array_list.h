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
 *
 *          Array based implementation of a list
 */


#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>


template <class T> class array_list
{

private:

    size_t length;
    size_t maxLength;

    T* data;

public:

    array_list():length(0),maxLength(2)
    {
        data = new T[2];
    }

    virtual ~array_list()
    {
       delete[] data;
    }

    inline const size_t& size() const
    {
       return length;
    }

    inline const T& at(const int& index) const
    {
        return data[index];
    }

    void push_back(T item);

    void clear();

    void copyDataToArray(T* arrayPtr) const;
};

template<class T> void array_list<T>::copyDataToArray(T* arrayPtr) const
{
    memcpy(arrayPtr,data, length * sizeof(T));
}

template<class T> void array_list<T>::push_back(T item)
{

    if(length < maxLength)
    {
        data[length] = item;
        length++;

    }else{

        const T* tmpPtr = this->data;
        maxLength <<= 1;

        data = new T[maxLength];

        memcpy(data,tmpPtr, length * sizeof(T));

        data[length++] = item;

        delete[] tmpPtr;
    }

}

template<class T>  void array_list<T>::clear()
{
   this->length = 0;
   this->maxLength = 2;

   delete[] data;

   data = new T[2];
}

#endif // ARRAY_LIST_H
