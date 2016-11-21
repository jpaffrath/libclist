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

#include <list.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

element* create_list(const void* value, size_t value_size) {
	if (value == NULL || value_size <= 0) return NULL;

	element* root = (element*)malloc(sizeof(element));

	if (root == NULL) return NULL;

	root->value = (void*)malloc(value_size);
	root->next = NULL;

	memcpy(root->value, value, value_size);

	return root;
}

element* create_empty_list(void) {
	element* root = (element*)malloc(sizeof(element));

	if (root == NULL) return NULL;

	root->value = NULL;
	root->next = NULL;

	return root;
}

element* create_list_with_array(const void* values, size_t value_size, int length) {
	if (values == NULL || value_size <= 0 || length <= 0) return NULL;

	element* root = create_list(values, value_size);

	if (root == NULL) return NULL;

	element* iterator = root;

	int i;
	for (i = 1; i < length; i++) {
		iterator->next = create_list(values + (value_size * i), value_size);
		iterator = iterator->next;

		if (iterator == NULL) {
			delete_list(&root);
			return NULL;
		}
	}

	return root;
}

element* create_list_with_string(const char* str) {
	if (str == NULL) return NULL;

	element* root = create_list(&str[0], sizeof(char));

	if (root == NULL) return NULL;

	element* iterator = root;

	int i;
	for (i = 1; str[i] != '\0'; i++) {
		iterator->next = create_list(&str[i], sizeof(char));
		iterator = iterator->next;

		if (iterator == NULL) {
			delete_list(&root);
			return NULL;
		}
	}

	return root;
}

element* create_list_alloc(void* value, void* (alloc_callback)(const void* e)) {
	if (value == NULL || alloc_callback == NULL) return NULL;

	element* root = (element*)malloc(sizeof(element));

	if (root == NULL) return NULL;

	root->value = alloc_callback(value);
	root->next = NULL;

	return root;
}

void delete_list(element** list) {
	if (*list == NULL) return;

	element* del = *list;

	while (del->next != NULL) {
		element* last = del;
		del = del->next;

		free(last->value);
		free(last);
	}

	free(del->value);
	free(del);

	*list = NULL;
}

void delete_list_alloc(element** list, void (*free_callback)(const void* value)) {
	if (*list == NULL || free_callback == NULL) return;

	element* del = *list;

	while (del->next != NULL) {
		element* last = del;
		del = del->next;

		free_callback(last->value);
		free(last->value);
		free(last);
	}

	free_callback(del->value);
	free(del->value);
	free(del);

	*list = NULL;
}

element* clone_list(element* list, size_t value_size) {
	if (list == NULL || value_size <= 0) return NULL;

	element* new_list = create_list(list->value, value_size);

	if (new_list == NULL) return NULL;

	element* iterator = list->next;
	element* clone_iterator = new_list;

	while (iterator != NULL) {
		clone_iterator->next = create_list(iterator->value, value_size);
		clone_iterator = clone_iterator->next;
		iterator = iterator->next;
	}

	return new_list;
}

element* add_element(element* list, const void* value, size_t value_size) {
	if (list == NULL || value == NULL || value_size <= 0) return NULL;

	element* last_element = get_last_element(list);

	if (last_element == NULL) return NULL;

	last_element->next = create_list(value, value_size);

	if (last_element->next == NULL) return NULL;

	return last_element->next;
}

element* add_element_alloc(element* list, void* value, void* (alloc_callback)(const void* e)) {
	if (list == NULL || value == NULL || alloc_callback == NULL) return NULL;

	element* last_element = get_last_element(list);

	if (last_element == NULL) return NULL;

	last_element->next = create_list_alloc(value, alloc_callback);

	if (last_element->next == NULL) return NULL;

	return last_element->next;
}

element* add_element_at_index(element* list, const void* value, size_t value_size, int index) {
	if (index < 1 || list == NULL || value == NULL || value_size <= 0) return NULL;

	element* iterator = list;
	int counter = 0;

	while (counter < index - 1) {
		iterator = iterator->next;
		counter++;
	}

	element* element_before = iterator;
	element* element_after = iterator->next;

	if (element_before == NULL || element_after == NULL) return NULL;

	element* new_element = create_list(value, value_size);

	if (new_element == NULL) return NULL;

	element_before->next = new_element;
	new_element->next = element_after;

	return new_element;
}

element* remove_element_at_index(element* list, int index) {
	if (index < 1 || list == NULL) return NULL;

	if (index == 1) {
		element* target = list->next;
		free(target->value);
		list->next = target->next;
		free(target);

		return list;
	}

	element* iterator = list;
	int counter = 0;

	while (counter < index - 1) {
		iterator = iterator->next;
		counter++;
	}

	element* target = iterator->next;
	free(target->value);
	iterator->next = target->next;
	free(target);

	return iterator;
}

element* remove_elements_in_range(element* list, int range_start, int range_end) {
	int length = get_length_of_list(list);
	if (length == -1 || range_start < 1 || range_end > (length -1) || range_start > range_end) return NULL;

	int counter = range_start;

	while (counter <= range_end) {
		if (remove_element_at_index(list, range_start) == NULL) return NULL;
		counter++;
	}

	return list;
}

element* get_element_at_index(element* list, int index) {
	if (index < 0 || list == NULL) return NULL;

	element* iterator = list;
	int counter = 0;

	while (counter < index) {
		iterator = iterator->next;
		if (iterator == NULL) return NULL;
		counter++;
	}

	return iterator;
}

void* get_value_at_index(element* list, int index) {
	element* e = get_element_at_index(list, index);

	if (e == NULL) return NULL;

	return e->value;
}

element* set_value_at_index(element* list, const void* value, size_t value_size, int index) {
	if (list == NULL || value == NULL || value_size == 0 || index < 0) return NULL;

	element* e = get_element_at_index(list, index);

	if (e == NULL) return NULL;

	free(e->value);

	e->value = (void*)malloc(value_size);
	memcpy(e->value, value, value_size);

	return e;
}

element* get_last_element(element* list) {
	if (list == NULL) return NULL;

	element* iterator = list;

	while (iterator->next != NULL) {
		iterator = iterator->next;
	}

	return iterator;
}

element* swap_elements(element* list, int index_a, int index_b) {
	if (list == NULL || index_a < 1 || index_b < 1) return NULL;

	element* e_a = get_element_at_index(list, index_a);
	element* e_b = get_element_at_index(list, index_b);

	if (e_a == NULL || e_b == NULL) return NULL;

	element* e_a_before = get_element_at_index(list, index_a - 1);
	element* e_b_before = get_element_at_index(list, index_b - 1);

	if (e_a_before == NULL || e_b_before == NULL) return NULL;

	element* e_swap = e_b->next;

	e_a_before->next = e_b;
	e_b->next = e_a->next;
	e_b_before->next = e_a;
	e_a->next = e_swap;

	return list;
}

int get_length_of_list(element* list) {
	if (list == NULL) return -1;

	element* iterator = list;
	int counter = 1;

	while (iterator->next != NULL) {
		iterator = iterator->next;
		counter++;
	}

	return counter;
}

int contains_element(element* list, element* e) {
	if (list == NULL || e == NULL) return -1;

	element* iterator = list;
	int counter = 0;
	int length = get_length_of_list(list);

	if (length == -1) return -1;

	while (counter < length) {
		if (iterator == e) return counter;

		iterator = iterator->next;
		counter++;
	}

	return -1;
}

int contains_value(element* list, const void* value, size_t size) {
	if (list == NULL || value == NULL) return -1;

	element* iterator = list;
	int counter = 0;
	int length = get_length_of_list(list);

	if (length == -1) return -1;

	while (counter < length) {
		if (memcmp(iterator->value, value, size) == 0) return counter;

		iterator = iterator->next;
		counter++;
	}

	return -1;
}

char* list_to_string(element* list) {
	if (list == NULL) return NULL;

	element* iterator = list;
	int length = get_length_of_list(list);
	char* str = (char*)malloc(get_length_of_list(list) + 1);
	int counter = 0;

	while (counter < length) {
		str[counter] = *(char*)iterator->value;
		iterator = iterator->next;
		counter++;
	}

	str[length] = '\0';

	return str;
}

void print_list(element* list) {
	if (list == NULL) return;

	element* iterator = list;
	int counter = 0;

	puts("***");
	printf("\t[%d]: %s\n", counter++, (char*)iterator->value);

	while (iterator->next != NULL) {
		iterator = iterator->next;
		printf("\t[%d]: %s\n", counter++, (char*)iterator->value);
	}

	puts("***");
}