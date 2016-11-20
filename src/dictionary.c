#include <dictionary.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

entry* create_dictionary(const void* value, size_t value_size, const char* key) {
	if (value == NULL || value_size <= 0 || key == NULL) return NULL;

	entry* root = (entry*)malloc(sizeof(entry));

	if (root == NULL) return NULL;

	size_t str_len = strlen(key);

	root->value = (void*)malloc(value_size);
	root->key = (char*)malloc(str_len + 1);
	root->next = NULL;

	memcpy(root->value, value, value_size);
	strcpy(root->key, key);

	return root;
}

void delete_dictionary(entry** dictionary) {
	if (*dictionary == NULL) return;

	entry* del = *dictionary;

	while (del->next != NULL) {
		entry* last = del;
		del = del->next;

		free(last->value);
		free(last->key);
		free(last);
	}

	free(del->value);
	free(del->key);
	free(del);

	*dictionary = NULL;
}

entry* clone_dictionary(entry* dictionary, size_t value_size) {
	if (dictionary == NULL || value_size <= 0) return NULL;

	entry* new_dict = create_dictionary(dictionary->value, value_size, dictionary->key);

	if (new_dict == NULL) return NULL;

	entry* iterator = dictionary->next;
	entry* clone_iterator = new_dict;

	while (iterator != NULL) {
		clone_iterator->next = create_dictionary(iterator->value, value_size, iterator->key);
		clone_iterator = clone_iterator->next;
		iterator = iterator->next;
	}

	return new_dict;
}

entry* add_entry(entry* dictionary, const void* value, size_t value_size, const char* key) {
	if (dictionary == NULL || value == NULL || value_size <= 0 || key == NULL) return NULL;

	entry* e = get_entry(dictionary, key);

	if (e != NULL) {
		free(e->value);
		e->value = (void*)malloc(value_size);
		if (e->value == NULL) return NULL;
		memcpy(e->value, value, value_size);

		return e;
	}

	entry* last = dictionary;
	while (last->next != NULL) last = last->next;

	last->next = create_dictionary(value, value_size, key);

	if (last->next == NULL) return NULL;

	return last->next;
}

entry* remove_entry(entry* dictionary, const char* key) {
	if (dictionary == NULL || key == NULL) return NULL;

	entry* iterator = dictionary;

	do {
		if (strcmp(iterator->next->key, key) == 0) {
			entry* target = iterator->next;
			free(target->value);
			free(target->key);
			iterator->next = target->next;
			free(target);

			return iterator;
		}
		iterator = iterator->next;
	}
	while (iterator != NULL);

	return NULL;
}

entry* get_entry(entry* dictionary, const char* key) {
	if (dictionary == NULL || key == NULL) return NULL;

	entry* iterator = dictionary;

	do {
		if (strcmp(iterator->key, key) == 0) {
			return iterator;
		}
		iterator = iterator->next;
	}
	while (iterator != NULL);

	return NULL;
}

int get_number_of_entries(entry* dictionary) {
	if (dictionary == NULL) return -1;

	entry* iterator = dictionary;
	int counter = 1;

	while (iterator->next != NULL) {
		iterator = iterator->next;
		counter++;
	}

	return counter;
}

int contains_key(entry* dictionary, const char* key) {
	if (dictionary == NULL) return -1;

	entry* iterator = dictionary;
	int counter = 0;

	while (iterator->next != NULL) {
		if (strcmp(iterator->key, key) == 0) return counter;
		iterator = iterator->next;
		counter++;
	}

	return -1;
}

element* get_keys(entry* dictionary) {
	if (dictionary == NULL) return NULL;

	element* list = create_list(dictionary->key, strlen(dictionary->key) + 1);

	entry* iterator = dictionary;

	while (iterator->next != NULL) {
		iterator = iterator->next;
		add_element(list, iterator->key, strlen(iterator->key) + 1);
	}

	return list;
}

void print_dictionary(entry* dicionary) {
	if (dicionary == NULL) return;

	entry* iterator = dicionary;

	puts("***");
	printf("\t%s -> %s\n", iterator->key, (char*)iterator->value);

	while (iterator->next != NULL) {
		iterator = iterator->next;
		printf("\t%s -> %s\n", iterator->key, (char*)iterator->value);
	}

	puts("***");
}