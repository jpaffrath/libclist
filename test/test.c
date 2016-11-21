#include "../include/libclist.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

void test_list(void);
void test_dictionary(void);

void test_int_list(void);
void test_char_list(void);

void test_list_performance(void);

/* TEST MAIN */

int main(int argc, char* argv[]) {
	if (argc > 1 && strcmp(argv[1], "--performance") == 0) {
		test_list_performance();
		return EXIT_SUCCESS;
	}

	CU_TestInfo tests[] = {
		{"test of list", test_list},
		{"test of dictionary", test_dictionary},
		{"test of int list", test_int_list},
		{"test of char list", test_char_list},
		CU_TEST_INFO_NULL,
	};

	CU_SuiteInfo suites[] = {
		{"Suite libclist", NULL, NULL, tests},
		CU_SUITE_INFO_NULL,
	};

	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}

	if (CU_register_suites(suites) != CUE_SUCCESS) {
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}

/* TEST FUNCTIONS */

typedef struct test_struct_ptr {
	char* str;
} test_struct_ptr;

static void* alloc_callback(const void* e) {
	test_struct_ptr* old = (test_struct_ptr*)e;
	test_struct_ptr* new = (test_struct_ptr*)malloc(sizeof(test_struct_ptr));
	new->str = (char*)malloc(strlen(old->str) + 1);
	strcpy(new->str, old->str);

	return new;
}

static void free_callback(const void* e) {
	test_struct_ptr* ptr = (test_struct_ptr*)e;
	free(ptr->str);
}

void test_list(void) {
	const int valueInt = -42;
	const char valueChar = 'J';
	const double valueDouble = 3.3;
	const char* valueString = "Test";

	element* list = create_list(&valueInt, sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(list);

	CU_ASSERT_EQUAL(get_length_of_list(list), 1);

	CU_ASSERT_PTR_NOT_NULL(add_element(list, &valueChar, sizeof(char)));
	CU_ASSERT_PTR_NOT_NULL(add_element(list, &valueDouble, sizeof(double)));
	CU_ASSERT_PTR_NOT_NULL(add_element(list, valueString, strlen("Test") + 1));

	CU_ASSERT_EQUAL(contains_element(list, get_last_element(list)), 3);

	const int testValInt = valueInt;
	CU_ASSERT_NOT_EQUAL(contains_value(list, &testValInt, sizeof(testValInt)), -1);
	CU_ASSERT_EQUAL(contains_value(list, "Test", strlen("Test")), 3);

	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list, 0), valueInt);
	CU_ASSERT_EQUAL(*(char*)get_value_at_index(list, 1), valueChar);
	CU_ASSERT_EQUAL(*(double*)get_value_at_index(list, 2), valueDouble);

	CU_ASSERT_STRING_EQUAL((char*)get_value_at_index(list, 3), valueString);

	add_element_at_index(list, &valueInt, sizeof(int), 1);
	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list, 0), valueInt);
	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list, 1), valueInt);
	CU_ASSERT_EQUAL(*(char*)get_value_at_index(list, 2), valueChar);

	CU_ASSERT_PTR_NOT_NULL(remove_element_at_index(list, 3));

	CU_ASSERT_PTR_NOT_NULL(set_value_at_index(list, &valueDouble, sizeof(double), 1));

	delete_list(&list);
	CU_ASSERT_PTR_NULL(list);

	element* list_str = create_list_with_string("123456789");
	CU_ASSERT_PTR_NOT_NULL(list_str);

	char* result = list_to_string(list_str);
	CU_ASSERT_PTR_NOT_NULL(result);
	CU_ASSERT_STRING_EQUAL(result, "123456789");
	if (result) free(result);

	CU_ASSERT_PTR_NOT_NULL(swap_elements(list_str, 1, 3));
	result = list_to_string(list_str);
	CU_ASSERT_PTR_NOT_NULL(result);
	CU_ASSERT_STRING_EQUAL(result, "143256789");
	if (result) free(result);

	CU_ASSERT_PTR_NOT_NULL(swap_elements(list_str, 5, 8));
	result = list_to_string(list_str);
	CU_ASSERT_PTR_NOT_NULL(result);
	CU_ASSERT_STRING_EQUAL(result, "143259786");
	if (result) free(result);

	CU_ASSERT_PTR_NOT_NULL(remove_elements_in_range(list_str, 1, 4));
	result = list_to_string(list_str);
	CU_ASSERT_PTR_NOT_NULL(result);
	CU_ASSERT_STRING_EQUAL(result, "19786");
	if (result) free(result);

	delete_list(&list_str);
	CU_ASSERT_PTR_NULL(list_str);

	typedef struct test_struct {
		int val_i;
		char val_c;
	} test_struct;

	test_struct s;
	s.val_i = 7;
	s.val_c = 'J';

	element* list_struct = create_list(&s, sizeof(test_struct));
	CU_ASSERT_PTR_NOT_NULL(list_struct);

	CU_ASSERT_PTR_NOT_NULL(add_element(list_struct, &s, sizeof(test_struct)));
	CU_ASSERT_PTR_NOT_NULL(add_element(list_struct, &s, sizeof(test_struct)));
	CU_ASSERT_PTR_NOT_NULL(add_element(list_struct, &s, sizeof(test_struct)));

	test_struct new_struct = *(test_struct*)get_value_at_index(list_struct, 1);
	CU_ASSERT_EQUAL(new_struct.val_i, 7);
	CU_ASSERT_EQUAL(new_struct.val_c, 'J');

	delete_list(&list_struct);
	CU_ASSERT_PTR_NULL(list_struct);

	test_struct_ptr ptr;
	ptr.str = (char*)malloc(10);
	strcpy(ptr.str, "123456789");
	ptr.str[9] = '\0';

	element* list_struct_ptr = create_list_alloc(&ptr, alloc_callback);
	CU_ASSERT_PTR_NOT_NULL(list_struct_ptr);

	CU_ASSERT_PTR_NOT_NULL(add_element_alloc(list_struct_ptr, &ptr, alloc_callback));

	test_struct_ptr* val = (test_struct_ptr*)get_value_at_index(list_struct_ptr, 1);
	CU_ASSERT_STRING_EQUAL(val->str, ptr.str);

	free(ptr.str);
	delete_list_alloc(&list_struct_ptr, free_callback);
	CU_ASSERT_PTR_NULL(list_struct_ptr);

	element* list_to_clone = create_list(&valueInt, sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(list_to_clone);

	CU_ASSERT_PTR_NOT_NULL(add_element(list_to_clone, &valueInt, sizeof(int)));

	element* clone = clone_list(list_to_clone, sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(clone);

	delete_list(&list_to_clone);
	CU_ASSERT_PTR_NULL(list_to_clone);

	CU_ASSERT_EQUAL(get_length_of_list(clone), 2);

	CU_ASSERT_EQUAL(*(int*)get_value_at_index(clone, 0), valueInt);

	delete_list(&clone);
	CU_ASSERT_PTR_NULL(clone);

	element* list_empty = create_empty_list();
	CU_ASSERT_PTR_NOT_NULL(list_empty);
	CU_ASSERT_PTR_NULL(list_empty->value);
	CU_ASSERT_PTR_NULL(list_empty->next);

	set_value_at_index(list_empty, &valueInt, sizeof(int), 0);
	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list_empty, 0), valueInt);

	delete_list(&list_empty);
	CU_ASSERT_PTR_NULL(list_empty);

	int intValues[4] = {3, -75, 1, 88};

	element* list_array = create_list_with_array(intValues, sizeof(int), 4);
	CU_ASSERT_PTR_NOT_NULL(list_array);

	CU_ASSERT_EQUAL(get_length_of_list(list_array), 4);

	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list_array, 0), 3);
	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list_array, 1), -75);
	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list_array, 2), 1);
	CU_ASSERT_EQUAL(*(int*)get_value_at_index(list_array, 3), 88);

	delete_list(&list_array);
	CU_ASSERT_PTR_NULL(list_array);
}

void test_dictionary(void) {
	const int valueInt = -42;
	const char valueChar = 'J';
	const double valueDouble = 3.3;
	const char* valueString = "Test";

	entry* dict = create_dictionary(&valueInt, sizeof(int), "valueInt");
	CU_ASSERT_PTR_NOT_NULL(dict);

	CU_ASSERT_EQUAL(get_number_of_entries(dict), 1);

	CU_ASSERT_PTR_NOT_NULL(add_entry(dict, &valueChar, sizeof(char), "valueChar"));
	CU_ASSERT_PTR_NOT_NULL(add_entry(dict, valueString, strlen(valueString)+1, "valueString"));
	CU_ASSERT_PTR_NOT_NULL(add_entry(dict, &valueDouble, sizeof(double), "valueDouble"));

	CU_ASSERT_EQUAL(get_number_of_entries(dict), 4);

	entry* e = get_entry(dict, "valueString");
	CU_ASSERT_PTR_NOT_NULL(e);
	CU_ASSERT_STRING_EQUAL(e->value, valueString);

	CU_ASSERT_PTR_NOT_NULL(remove_entry(dict, "valueChar"));

	e = get_entry(dict, "valueString");
	CU_ASSERT_PTR_NOT_NULL(e);
	CU_ASSERT_STRING_EQUAL(e->value, valueString);

	delete_dictionary(&dict);
	CU_ASSERT_PTR_NULL(dict);

	entry* dict_to_clone = create_dictionary(&valueInt, sizeof(int), "valueInt");
	CU_ASSERT_PTR_NOT_NULL(dict_to_clone);

	CU_ASSERT_PTR_NOT_NULL(add_entry(dict_to_clone, &valueInt, sizeof(int), "valueInt1"));
	CU_ASSERT_PTR_NOT_NULL(add_entry(dict_to_clone, &valueInt, sizeof(int), "valueInt2"));
	CU_ASSERT_PTR_NOT_NULL(add_entry(dict_to_clone, &valueInt, sizeof(int), "valueInt3"));
	CU_ASSERT_PTR_NOT_NULL(add_entry(dict_to_clone, &valueInt, sizeof(int), "valueInt4"));

	CU_ASSERT_EQUAL(contains_key(dict_to_clone, "valueInt2"), 2);
	CU_ASSERT_EQUAL(contains_key(dict_to_clone, "noKey"), -1);

	entry* clone = clone_dictionary(dict_to_clone, sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(clone);

	delete_dictionary(&dict_to_clone);
	CU_ASSERT_PTR_NULL(dict_to_clone);

	CU_ASSERT_EQUAL(get_number_of_entries(clone), 5);

	delete_dictionary(&clone);
	CU_ASSERT_PTR_NULL(clone);
}

void test_list_performance(void) {
	int i = 0;
	int max = 10000;

	clock_t start = clock();

	element* list = create_list(&i, sizeof(int));

	for (i = 1; i < max; i++) {
		add_element(list, &i, sizeof(int));
	}

	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;

	printf("Storing %d values has taken %f seconds\n", max, seconds);

	delete_list(&list);
}

void test_int_list(void) {
	element* int_list = create_int_list(2);
	CU_ASSERT_PTR_NOT_NULL(int_list);

	CU_ASSERT_EQUAL(get_length_of_list(int_list), 1);

	int i;
	for (i = 0; i < 50; i++) {
		CU_ASSERT_PTR_NOT_NULL(add_int_element(int_list, i));
	}

	for (i = 1; i < 50; i++) {
		CU_ASSERT_EQUAL(get_int_at_index(int_list, i), i - 1);
	}

	CU_ASSERT_EQUAL(get_length_of_list(int_list), 51);
	CU_ASSERT_EQUAL(contains_int(int_list, 20), 21);

	for (i = 0; i < get_length_of_list(int_list); i++) {
		CU_ASSERT_PTR_NOT_NULL(set_int_at_index(int_list, 100, i));
	}

	for (i = 0; i < get_length_of_list(int_list); i++) {
		CU_ASSERT_EQUAL(get_int_at_index(int_list, i), 100);
	}

	CU_ASSERT_PTR_NOT_NULL(add_int_element_at_index(int_list, 42, 30));
	CU_ASSERT_EQUAL(get_int_at_index(int_list, 30), 42);
	CU_ASSERT_EQUAL(get_length_of_list(int_list), 52);

	delete_list(&int_list);
	CU_ASSERT_PTR_NULL(int_list);
}

void test_char_list(void) {
	element* char_list = create_char_list('A');
	CU_ASSERT_PTR_NOT_NULL(char_list);

	CU_ASSERT_EQUAL(get_length_of_list(char_list), 1);

	int i;
	for (i = 0; i < 50; i++) {
		CU_ASSERT_PTR_NOT_NULL(add_char_element(char_list, (char)i));
	}

	for (i = 1; i < 50; i++) {
		CU_ASSERT_EQUAL(get_char_at_index(char_list, i), (char)(i - 1));
	}

	CU_ASSERT_EQUAL(get_length_of_list(char_list), 51);
	CU_ASSERT_EQUAL(contains_char(char_list, 20), (char)21);

	for (i = 0; i < get_length_of_list(char_list); i++) {
		CU_ASSERT_PTR_NOT_NULL(set_char_at_index(char_list, 100, i));
	}

	for (i = 0; i < get_length_of_list(char_list); i++) {
		CU_ASSERT_EQUAL(get_char_at_index(char_list, i), 100);
	}

	CU_ASSERT_PTR_NOT_NULL(add_char_element_at_index(char_list, 42, 30));
	CU_ASSERT_EQUAL(get_char_at_index(char_list, 30), (char)42);
	CU_ASSERT_EQUAL(get_length_of_list(char_list), 52);

	delete_list(&char_list);
	CU_ASSERT_PTR_NULL(char_list);
}