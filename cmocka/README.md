# [TDD Boot - cmocka](https://github.com/djboni/tdd-boot)

The test runner is created manually.
The test functions must be manually added to the `main()` function.

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

/* These four must be included before cmocka.h. */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* Include unit-test headers and fake/mocks. */
#include "cmocka.h"

/* Suite set-up: runs once before the first test. */
int suiteSetUp(void **state)
{
    (void)state;
    return 0;
}

/* Suite tear-down: runs once after the last test. */
int suiteTearDown(void **state)
{
    (void)state;
    return 0;
}

/* Test set-up: runs before each test. */
int setUp(void **state)
{
    (void)state;
    return 0;
}

/* Test tear-down: runs after each test. */
int tearDown(void **state)
{
    (void)state;
    return 0;
}

/*
 * Test naming convention:
 *
 * - test_Function_Parameters_ExpectedResult (function)
 * - test_Context_Interaction_ExpectedReaction (system)
 * - test_Given_When_Then (analogy to Cucumber scenarios)
 */

void test_Sum_ZeroZero_ReturnZero(void **state)
{
    (void)state;

    assert_int_equal(0, Sum(0, 0));
}

void test_Sum_OneZero_ReturnOne(void **state)
{
    (void)state;

    assert_int_equal(1, Sum(1, 0));
}

void test_Sum_ZeroOne_ReturnOne(void **state)
{
    (void)state;

    assert_int_equal(1, Sum(0, 1));
}

void test_Sum_OneOne_ReturnTwo(void **state)
{
    (void)state;

    assert_int_equal(2, Sum(1, 1));
}

void test_Sum_ThreeFive_ReturnEight(void **state)
{
    (void)state;

    assert_int_equal(8, Sum(3, 5));
}

/* Main function: test runner. */

int main(void)
{
    /* Tests must be added manually. */
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(
            test_Sum_ZeroZero_ReturnZero, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sum_OneZero_ReturnOne, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sum_ZeroOne_ReturnOne, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sum_OneOne_ReturnTwo, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sum_ThreeFive_ReturnEight, setUp, tearDown),
    };

    return cmocka_run_group_tests(tests, suiteSetUp, suiteTearDown);
}
```
