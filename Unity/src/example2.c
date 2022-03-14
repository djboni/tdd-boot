#include <stdint.h>

int32_t Sub(int32_t x, int32_t y)
{
    return x - y;
}

#ifdef UNITTEST
    #include "unity.h"

void suiteSetUp(void)
{
}

int suiteTearDown(int num_failures)
{
    return num_failures;
}

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Sub_ZeroZero_ReturnZero(void)
{
    TEST_ASSERT_EQUAL(0, Sub(0, 0));
}

void test_Sub_OneZero_ReturnOne(void)
{
    TEST_ASSERT_EQUAL(1, Sub(1, 0));
}

void test_Sub_ZeroOne_ReturnMinusOne(void)
{
    TEST_ASSERT_EQUAL(-1, Sub(0, 1));
}

void test_Sub_OneOne_ReturnZero(void)
{
    TEST_ASSERT_EQUAL(0, Sub(1, 1));
}

void test_Sub_ThreeFive_ReturnMinusTwo(void)
{
    TEST_ASSERT_EQUAL(-2, Sub(3, 5));
}

#endif /* UNITTEST */
