# [TDD Boot - Unity](https://github.com/djboni/tdd-boot)

The test runner is created using the script
`unity/auto/generate_test_runner.rb`.
This script defines the function `main()` and calls the test functions.

```c
/* File: sum.c. */

#include "sum.h"

int32_t Sum(int32_t x, int32_t y)
{
    return x + y;
}
```

```c
/* File: sum_test.c with additional comments. */

#include "sum.h"

/* Include unit-test headers and fake/mocks. */
#include "unity.h"

/* Suite set-up: runs once before the first test. */
void suiteSetUp(void)
{
}

/* Suite tear-down: runs once after the last test. */
int suiteTearDown(int num_failures)
{
    return num_failures;
}

/* Test set-up: runs before each test. */
void setUp(void)
{
}

/* Test tear-down: runs after each test. */
void tearDown(void)
{
}

/*
 * Test naming convention:
 *
 * - test_Function_Parameters_ExpectedResult (function)
 * - test_Context_Interaction_ExpectedReaction (system)
 * - test_Given_When_Then (analogy to Cucumber scenarios)
 */

void test_Sum_ZeroZero_ReturnZero(void)
{
    TEST_ASSERT_EQUAL(0, Sum(0, 0));
}

void test_Sum_OneZero_ReturnOne(void)
{
    TEST_ASSERT_EQUAL(1, Sum(1, 0));
}

void test_Sum_ZeroOne_ReturnOne(void)
{
    TEST_ASSERT_EQUAL(1, Sum(0, 1));
}

void test_Sum_OneOne_ReturnTwo(void)
{
    TEST_ASSERT_EQUAL(2, Sum(1, 1));
}

void test_Sum_ThreeFive_ReturnEight(void)
{
    TEST_ASSERT_EQUAL(8, Sum(3, 5));
}
```
