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

#ifndef LIBC_DICTIONARY
#define LIBC_DICTIONARY

#include "list.h"
#include <stddef.h>

struct entry {
	void* value;
	char* key;
	struct entry* next;
};

typedef struct entry entry;

/**
* @brief Creates a new dictionary and initializes it with the given value-key pair
*
* @param value address of the value
* @param value_size size of the value
* @param key string representing the key
*
* @return pointer to the new dictionary or NULL
*/
entry* create_dictionary(const void* value, size_t value_size, const char* key);

/**
* @brief Deletes a given dictionary and all of its entries
*
* @param dictionary pointer to dictionary
*/
void delete_dictionary(entry** dictionary);

/**
* @brief Clones a given dicionary and all of its entries into a new allocated dictioary
*
* @param dictionary the dictionary to be cloned
* @param value_size size of the entries values
*
* @return pointer to the new cloned dictionary or NULL
*/
entry* clone_dictionary(entry* dictionary, size_t value_size);

/**
* @brief Adds a new value-key pair to a given dictionary
*
* If the given key already exists, the value of this entry
* is updated with the given value.
*
* @param dictionary dictionary for adding the new pair to
* @param value address of the value
* @param value_size size of the value
* @param key string representing the key
*
* @return pointer to the new entry or NULL
*/
entry* add_entry(entry* dictionary, const void* value, size_t value_size, const char* key);


/**
* @brief Removes an entry with a given key
*
* @param dictionary dictionary containing entries
* @param key key of the entry
*
* @return pointer to the dictionary or NULL
*/
entry* remove_entry(entry* dictionary, const char* key);

/**
* @brief Returns the entry with the given key
*
* @param dictionary dictionary containing entries
* @param key key of the entry
*
* @return pointer to the entry with the given key or NULL
*/
entry* get_entry(entry* dictionary, const char* key);

/**
* @brief Returns the number of entries of a given dictionary
*
* @param dictionary dictionary containing entries
*
* @return the number of entries or -1
*/
int get_number_of_entries(entry* dictionary);

/**
* @brief Checks if a given key is part of a given dictionary
*
* @param dictionary dictionary containing entries
* @param key key to search for
*
* @return the index of the entry matching the key or -1
*/
int contains_key(entry* dictionary, const char* key);

/**
* @brief Returns a list containing the keys from a given dictionary
*
* @param dictionary dictionary containing entries
*
* @return a new allocated list containing the keys
*/
element* get_keys(entry* dictionary);

/**
* @brief Prints a representation of a given dictionary
*
* Note that currently only string values are displayed correctly
*/
void print_dictionary(entry* dicionary);

#endif