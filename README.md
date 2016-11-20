<p>
    <a href="https://github.com/jpaffrath/libclist">
        <img src="https://img.shields.io/badge/memcheck-passed-orange.svg"
             alt="Memcheck Badge">
    </a>
    <a href="https://github.com/jpaffrath/libclist/tree/master/test">
        <img src="https://img.shields.io/badge/test-passing-green.svg"
             alt="Java Badge">
    </a>
     <a href="https://github.com/jpaffrath/libclist/blob/master/LICENSE">
        <img src="https://img.shields.io/badge/license-GPL--3.0-blue.svg"
             alt="License Badge">
    </a>
</p>

# Introduction #
libclist is a shared library for the c programming language with list and dictionary implementations.

## Compile ##
Invoke *make* in the project root. This will build libclist as a shared library (libclist.so).

## Install ##
Invoke *sudo make install* in the project root. This will install the required header files along with the library to /usr/local/.

## Testing ##
The test/ directory contains unit tests build with CUnit.
Invoke *make* in the test/ directory will build a test binary. libclist and CUnit have to be installed first.

# list #
Provides an interface for a very fast linked list data structure. libclist supports storing any kind of data.
```c
#include <libclist/list.h>

int myVal = 5;

// create a new list holding your variable
element* list = create_list(&myVal, sizeof(int));

// add elements to your list
int myVal2 = 10;
add_element(list, &myVal2, sizeof(int));
```
List supports lists holding values of different types:
```c
int intVal = 5;
char charVal = 'J';
struct my_struct s;

element* list = create_list(&intVal, sizeof(int));
add_element(list, &charVal, sizeof(char));
add_element(list, &s, sizeof(struct my_struct));
```
Get an element or the value of an element is easy:
```c
intVal = *(int*)get_value_at_index(list, 0);
charVal = *(char*)get_value_at_index(list, 1);
```
If you are done using your list, do not forget to delete it!
```c
delete_list(&list);
```
If you want to store structs with allocated pointers, please use the _alloc_ functions provided:
```c
test_struct ptr;
ptr.str = (char*)malloc(100);

element* list = create_list_alloc(&ptr, alloc_callback);
[...]
delete_list_alloc(&list, free_callback);
```
These functions are taking function pointers for allocating and freeing pointers in your struct:
```c
static void* alloc_callback(const void* e) {
	test_struct* s = (test_struct*)e;
	test_struct* copy = (test_struct*)malloc(sizeof(test_struct));
	new->str = (char*)malloc(100);
	strcpy(copy->str, s->str);
	return copy;
}

static void free_callback(const void* e) {
	test_struct* ptr = (test_struct*)e;
	free(ptr->str);
}
```
List supports a lot of useful list functions, just like removing or swapping elements, removing elements in a range, creating list from arrays or strings, or cloning lists. See list.h for all implemented functions.
