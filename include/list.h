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

#ifndef LIBC_LIST
#define LIBC_LIST

#include <stddef.h>

struct element {
	void* value;
	struct element* next;
};

typedef struct element element;

/**
* @brief Creates a new list and initializes it with a given value
*
* @param value address of the value
* @param value_size size of the value
*
* @return pointer to the new list or NULL
*/
element* create_list(const void* value, size_t value_size);

/**
* @brief Creates a new empty list
*
* The first item has to be added with set_value_at_index with index 0
*
* @return pointer to the new empty list or NULL
*/
element* create_empty_list(void);

/**
* @brief Creates a new list containing the elements from the given array
*
* @param values pointer to an array containing values
* @param value_size size of the array elements
* @param length length of the array
*
* @return pointer to the new list or NULL
*/
element* create_list_with_array(const void* values, size_t value_size, int length);

/**
* @brief Creates a new list containing the characters out of the given string
*
* @param str string which holds the characters
*
* @return pointer to the new list or NULL
*/
element* create_list_with_string(const char* str);

/**
* @brief Creates a new list and initializes it with a given value
*
* This function is designed for struct elements containing pointers.
* It takes a pointer pointing to a function which should return an allocated struct
* containing the allocated pointers.
*
* To delete a list created by this function, call delete_list_alloc which takes
* a pointer to a function where the struct's pointers should be released.
*
* @param value pointer address of the value
* @param alloc_callback function which allocates custom struct's
*
* @return pointer to the new list or NULL
*/
element* create_list_alloc(void* value, void* (alloc_callback)(const void* e));

/**
* @brief Deletes a given list and all of its elements
*
* @param list pointer to a list
*/
void delete_list(element** list);

/**
* @brief Deletes a given list and all of its elements using a customized free function
*
* This function is designed to delete a list created by create_list_alloc.
* For every element of the list, the free callback will be called which will free
* allocated pointers in struct's.
*
* @param list pointer to a list
* @param free_callback function which frees custom struct's pointers.
*/
void delete_list_alloc(element** list, void (*free_callback)(const void* value));

/**
* @brief Clones a given list and all of its elements into a new allocated list
*
* @param list the list to be cloned
* @param value_size size of the elements values
*
* @return pointer to the new cloned list or NULL
*/
element* clone_list(element* list, size_t value_size);

/**
* @brief Adds a new element to a given list
*
* @param list list for adding the new element to
* @param value address of the value
* @param value_size size of the value
*
* @return pointer to the new element or NULL
*/
element* add_element(element* list, const void* value, size_t value_size);

/**
* @brief Adds a new element to a list created by create_list_alloc
*
* @param list list for adding the new element to
* @param value address of the value
* @param alloc_callback the callback used for allocating struct's in create_list_alloc
*
* @return pointer to the new element or NULL
*/
element* add_element_alloc(element* list, void* value, void* (alloc_callback)(const void* e));

/**
* @brief Adds a new element to a given list at a given index
*
* @param list list for adding the new element to
* @param value address of the value
* @param value_size size of the value
* @param index index of the element
*
* @return pointer to the new element or NULL
*/
element* add_element_at_index(element* list, const void* value, size_t value_size, int index);

/**
* @brief Removes an element at a given index
*
* @param list list containing elements
* @param index index of the element
*
* @return pointer to the element at position index - 1 or NULL
*/
element* remove_element_at_index(element* list, int index);

/**
* @brief Removes all elements from index range_start to index range_end
*
* @param list list containing elements
* @param range_start index to start with
* @param range_end index to end with
*
* @return pointer to the list or NULL
*/
element* remove_elements_in_range(element* list, int range_start, int range_end);

/**
* @brief Returns the element at a given index
*
* @param list list containing elements
* @param index index of the element
*
* @return pointer to the element at the given index or NULL
*/
element* get_element_at_index(element* list, int index);

/**
* @brief Returns the value of the element at a given index
*
* @param list list containing elements
* @param index index of the element
*
* @return pointer to the elements value at the given index or NULL
*/
void* get_value_at_index(element* list, int index);

/**
* @brief Sets the value of an existing element
*
* @param list list containing elements
* @param value the value to be set
* @param value_size the size of the value
* @param index index of the element for setting the new value
*
* @return pointer to the element or NULL
*/
element* set_value_at_index(element* list, const void* value, size_t value_size, int index);

/**
* @brief Returns the last element from a given list
*
* @param list list containing elements
*
* @return pointer to the last element or NULL
*/
element* get_last_element(element* list);

/**
* @brief Swaps two elements at given indexes
*
* @param list list containing elements
* @param index_a index of the first element to swap
* @param index_b index of the second element to swap
*
* @return pointer to the list or NULL
*/
element* swap_elements(element* list, int index_a, int index_b);

/**
* @brief Returns the length of a given list
*
* @param list list containing elements
*
* @return the length of the given list or -1
*/
int get_length_of_list(element* list);

/**
* @brief Checks if a given element is part of a given list
*
* This function compares the memory addresses, so elements
* with the same value will not be treated as matches.
*
* @param list list containing elements
* @param e element to check for
*
* @return the index of e in list or -1
*/
int contains_element(element* list, element* e);

/**
* @brief Checks if a given value is part of a given list
*
* This function compares the bytes, so elements
* with the same bytes will be treated as matches.
*
* @param list list containing elements
* @param value value to compare
* @param size size of the value
*
* @return the index of the element containing the value or -1
*/
int contains_value(element* list, const void* value, size_t size);

/**
* @brief Converts all element values to characters and builds a string
*
* @param list list containing character elements
*
* @return an allocated char* pointing to a string
*/
char* list_to_string(element* list);

/**
* @brief Prints a representation of a given list
*
* Note that currently only string values are displayed correctly
*/
void print_list(element* list);

#endif