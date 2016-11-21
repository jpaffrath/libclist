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

#include <list_int.h>

element* create_int_list(int value) {
	return create_list(&value, sizeof(int));
}

element* add_int_element(element* list, int value) {
	return add_element(list, &value, sizeof(int));
}

element* add_int_element_at_index(element* list, int value, int index) {
	return add_element_at_index(list, &value, sizeof(int), index);
}

int get_int_at_index(element* list, int index) {
	return *(int*)get_value_at_index(list, index);
}

element* set_int_at_index(element* list, int value, int index) {
	return set_value_at_index(list, &value, sizeof(int), index);
}

int contains_int(element* list, int value) {
	return contains_value(list, &value, sizeof(int));
}