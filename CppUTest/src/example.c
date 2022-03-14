#include <stdint.h>

int32_t Sum(int32_t x, int32_t y)
{
    return x + y;
}

#ifdef UNITTEST
    #include "CppUTest/TestHarness.h"

TEST_GROUP (Sum)
{
    void setup() {}
    void teardown() {}
};

TEST(Sum, ZeroZero_ReturnZero)
{
    LONGS_EQUAL(0, Sum(0, 0));
}

TEST(Sum, OneZero_ReturnOne)
{
    LONGS_EQUAL(1, Sum(1, 0));
}

TEST(Sum, ZeroOne_ReturnOne)
{
    LONGS_EQUAL(1, Sum(0, 1));
}

TEST(Sum, OneOne_ReturnTwo)
{
    LONGS_EQUAL(2, Sum(1, 1));
}

TEST(Sum, ThreeFive_ReturnEight)
{
    LONGS_EQUAL(8, Sum(3, 5));
}

#endif /* UNITTEST */
