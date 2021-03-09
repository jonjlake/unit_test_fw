
/* Custom includes */
#include "unit_test_fw.h"

/* Std includes */
#include <stdio.h>

/* Function prototypes */
void run_test(JON_TEST_ERR (*test_fxn)(void), char *test_name);

/* File globals */

typedef struct test_str
{
	JON_TEST_ERR (*test_fxn)(void);
	char *test_name;
	struct test_str *next;
} test_str;

typedef struct test_suite
{
	char *suite_name;
	test_str *test_list;
} test_suite;

test_suite fg_test_suite = { 0 };

/* Function implementations */

void run_all_tests(void)
{
//	run_test(test_gen_checksum_invsum_correct, "Correct inverse checksum");
//	run_test(test_gen_checksum_invsum_incorrect, "Incorrect inverse checksum");
	test_str *test_ptr;

	printf("--- Test Suite: %s ---\n", fg_test_suite.suite_name);

	for(test_ptr = fg_test_suite.test_list; test_ptr; test_ptr = test_ptr->next)
	{
		run_test(test_ptr->test_fxn, test_ptr->test_name);
	}
}

// Add a return here indicating if any failed, or were unrecognized
void run_test(JON_TEST_ERR (*test_fxn)(void), char *test_name)
{
	JON_TEST_ERR ret_err;

	ret_err = test_fxn();

	switch (ret_err)
	{
		case JON_TEST_ERR_NO_ERR:
			printf("Test: %s SUCCEEDED\n", test_name);
			break;
		case JON_TEST_ERR_ERR:
			printf("Test: %s FAILED\n", test_name);
			break;
		default:
			printf("Test: %s RESULT UNRECOGNIZED\n", test_name);
			break;
	}
}

void add_test(JON_TEST_ERR (*test_fxn)(void), char *test_name)
{
	test_str *p_new_test = (test_str *) calloc(1, sizeof(*p_new_test));
	int test_name_len = strlen(test_name);

//	printf("Adding test %s\n", test_name);

	p_new_test->test_name = (char *) calloc(test_name_len + 1, sizeof(*p_new_test->test_name));
	strncpy(p_new_test->test_name, test_name, test_name_len + 1);	
	
	p_new_test->test_fxn = test_fxn;

	if (!fg_test_suite.test_list)
	{
		fg_test_suite.test_list = p_new_test;
	}
	else
	{
		test_str *test_ptr = fg_test_suite.test_list;
		while(test_ptr->next)
		{
			test_ptr = test_ptr->next;
		}
		test_ptr->next = p_new_test;
	}	
}

void init_test_suite(char *suite_name)
{
	int suite_name_len = strlen(suite_name);
	
	fg_test_suite.suite_name = (char *) calloc(suite_name_len + 1, 
			sizeof(*fg_test_suite.suite_name));
	strncpy(fg_test_suite.suite_name, suite_name, suite_name_len + 1);

//	printf("Created suite %s\n", suite_name);
}

void delete_test_suite(void)
{
	test_str *test_ptr = fg_test_suite.test_list;

	while(test_ptr)
	{
		test_ptr = fg_test_suite.test_list->next;
		free(fg_test_suite.test_list);
		fg_test_suite.test_list = test_ptr;
	}

	free(fg_test_suite.suite_name);	
	/* Need to free linked list here */
}
