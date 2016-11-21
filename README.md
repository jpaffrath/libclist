<p>
    <a href="https://github.com/jpaffrath/libclist">
        <img src="https://img.shields.io/badge/memcheck-passed-orange.svg"
             alt="Memcheck Badge">
    </a>
    <a href="https://github.com/jpaffrath/libclist/tree/master/test">
        <img src="https://img.shields.io/badge/test-passed-green.svg"
             alt="Test Badge">
    </a>
     <a href="https://github.com/jpaffrath/libclist/blob/master/LICENSE">
        <img src="https://img.shields.io/badge/license-MIT-blue.svg"
             alt="License Badge">
    </a>
</p>

# Introduction #
libclist is a shared/static library for the c programming language with list and dictionary implementations.
libclist is very fast, yet memory saving and customizable. It is able to store any kind of data you like!

## Compile ##
Invoke *make* in the project root. This will build libclist as a shared (libclist.so) and as a static (libclist.a) library.

## Install ##
Invoke *sudo make install* in the project root. This will install the required header files along with the library to /usr/local/.

## Testing ##
The test/ directory contains unit tests build with CUnit.
Invoke *make* in the test/ directory will build a test binary.

# List API #
Provides a generic interface for a very fast linked list data structure. libclist supports storing any kind of data.
Just
```c
#include <libclist/list.h>
```
in your project and off you go!
Want a simple example? Take this:
```c
int myVal = 5;

// creates a new list holding your integer variable
element* list = create_list(&myVal, sizeof(int));

// adds an elements to your list
add_element(list, &myVal, sizeof(int));

// gets an element. You have to cast the result
int result = *(int*)get_element_at_index(list, 1);
```
Apart from the generic list interface, libclist provides a data type specialized API
```c
#include <libclist/list_int.h>
#include <libclist/list_char.h>
```
so you can use easier functions:
```c
element* myIntegerList = create_int_list(100);

printf("My list contains %d at index %d!", get_int_at_index(myIntegerList, 0), 0);
```
If you are done using your list, do not forget to delete it!
```c
delete_list(&list);
```

## A special case: structs with pointers! ##
If you want to store structs with allocated pointers, libclist provides specialized _create_ and _delete_ functions:
```c
test_struct myStruct;
myStruct.str = (char*)malloc(100);

element* list = create_list_alloc(&ptr, alloc_callback);
delete_list_alloc(&list, free_callback);
```
These functions are taking function pointers for allocating and freeing pointers in your struct.
You just have to define these functions by yourself.
See the following code for an easy example:
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
List supports a lot of useful functions, just like removing or swapping elements, removing elements in a range, creating list from arrays or strings, or cloning lists. See list.h for all implemented functions.
