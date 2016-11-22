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

#ifndef LIBC_LIST_DOUBLE
#define LIBC_LIST_DOUBLE

#include "list.h"

/**
* @brief Creates a new list and initializes it with a given double
*
* @param value double value
*
* @return pointer to the new list or NULL
*/
element* create_double_list(double value);

/**
* @brief Adds a new double to a given list
*
* @param list list for adding the new double to
* @param value double value
*
* @return pointer to the new element or NULL
*/
element* add_double_element(element* list, double value);

/**
* @brief Adds a new double to a given list at a given index
*
* @param list list for adding the new double to
* @param value double value
* @param index index of the element
*
* @return pointer to the new element or NULL
*/
element* add_double_element_at_index(element* list, double value, int index);

/**
* @brief Returns the double at a given index
*
* @param list list containing doubles
* @param index index of the double element
*
* @return double value at the given index or NULL
*/
double get_double_at_index(element* list, int index);

/**
* @brief Sets the value of an existing double
*
* @param list list containing doubles
* @param value the double value to be set
* @param index index of the element for setting the new double
*
* @return pointer to the element or NULL
*/
element* set_double_at_index(element* list, double value, int index);

/**
* @brief Checks if a given double is part of a given list
*
* This function compares the bytes, so elements
* with the same bytes will be treated as matches.
*
* @param list list containing doubles
* @param value double to compare
*
* @return the index of the element containing the value or -1
*/
int contains_double(element* list, double value);

#endif