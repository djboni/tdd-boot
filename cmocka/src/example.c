#include <stdint.h>

int32_t Sum(int32_t x, int32_t y)
{
    return x + y;
}

#if UNITTEST
    #include <setjmp.h>
    #include <stdarg.h>
    #include <stddef.h>
    #include <stdint.h>

    #include "cmocka.h"

int suiteSetUp(void **state)
{
    (void)state;
    return 0;
}

int suiteTearDown(void **state)
{
    (void)state;
    return 0;
}

int setUp(void **state)
{
    (void)state;
    return 0;
}

int tearDown(void **state)
{
    (void)state;
    return 0;
}

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

int main(void)
{
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

#endif /* UNITTEST */
