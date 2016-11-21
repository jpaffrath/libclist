/*
MIT License

Copyright (c) 2016 Julius Paffrath

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef LIBC_LIST_INT
#define LIBC_LIST_INT

#include "list.h"

/**
* @brief Creates a new list and initializes it with a given integer
*
* @param value integer value
*
* @return pointer to the new list or NULL
*/
element* create_int_list(int value);

/**
* @brief Adds a new integer to a given list
*
* @param list list for adding the new integer to
* @param value integer value
*
* @return pointer to the new element or NULL
*/
element* add_int_element(element* list, int value);

/**
* @brief Adds a new integer to a given list at a given index
*
* @param list list for adding the new integer to
* @param value integer value
* @param index index of the element
*
* @return pointer to the new element or NULL
*/
element* add_int_element_at_index(element* list, int value, int index);

/**
* @brief Returns the integer at a given index
*
* @param list list containing integers
* @param index index of the integer element
*
* @return integer value at the given index or NULL
*/
int get_int_at_index(element* list, int index);

/**
* @brief Sets the value of an existing integer
*
* @param list list containing integers
* @param value the integer value to be set
* @param index index of the element for setting the new integer
*
* @return pointer to the element or NULL
*/
element* set_int_at_index(element* list, int value, int index);

/**
* @brief Checks if a given integer is part of a given list
*
* This function compares the bytes, so elements
* with the same bytes will be treated as matches.
*
* @param list list containing integers
* @param value integer to compare
*
* @return the index of the element containing the value or -1
*/
int contains_int(element* list, int value);

#endif