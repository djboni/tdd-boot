#include <stdint.h>

int32_t Sub(int32_t x, int32_t y)
{
    return x - y;
}

#ifdef UNITTEST
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

void test_Sub_ZeroZero_ReturnZero(void **state)
{
    (void)state;

    assert_int_equal(0, Sub(0, 0));
}

void test_Sub_OneZero_ReturnOne(void **state)
{
    (void)state;

    assert_int_equal(1, Sub(1, 0));
}

void test_Sub_ZeroOne_ReturnMinusOne(void **state)
{
    (void)state;

    assert_int_equal(-1, Sub(0, 1));
}

void test_Sub_OneOne_ReturnZero(void **state)
{
    (void)state;

    assert_int_equal(0, Sub(1, 1));
}

void test_Sub_ThreeFive_ReturnMinusTwo(void **state)
{
    (void)state;

    assert_int_equal(-2, Sub(3, 5));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(
            test_Sub_ZeroZero_ReturnZero, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sub_OneZero_ReturnOne, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sub_ZeroOne_ReturnMinusOne, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sub_OneOne_ReturnZero, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Sub_ThreeFive_ReturnMinusTwo, setUp, tearDown),
    };

    return cmocka_run_group_tests(tests, suiteSetUp, suiteTearDown);
}

#endif /* UNITTEST */
