#include "sum.h"

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
