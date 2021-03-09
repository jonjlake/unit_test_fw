#ifndef UNIT_TEST_FW_H
#define UNIT_TEST_FW_H

/* Std includes */
#include <stdint.h>

/* Error return enum */
typedef enum JON_TEST_ERR
{
	JON_TEST_ERR_NO_ERR,
	JON_TEST_ERR_ERR,
} JON_TEST_ERR;

typedef struct test_results
{
	uint32_t num_succeeded;
	uint32_t num_failed;
	uint32_t num_unknown;
} test_results;

/* Function prototypes */
void init_test_suite(char *suite_name);
void delete_test_suite(void);
void add_test(JON_TEST_ERR (*test_fxn)(void), char *test_name);
void run_all_tests(void);


#endif // UNIT_TEST_FW_H
