#include <stdint.h>

int32_t Sub(int32_t x, int32_t y)
{
    return x - y;
}

#ifdef UNITTEST
    #include "CppUTest/TestHarness.h"

TEST_GROUP (Sub)
{
    void setup() {}
    void teardown() {}
};

TEST(Sub, ZeroZero_ReturnZero)
{
    LONGS_EQUAL(0, Sub(0, 0));
}

TEST(Sub, OneZero_ReturnOne)
{
    LONGS_EQUAL(1, Sub(1, 0));
}

TEST(Sub, ZeroOne_ReturnMinusOne)
{
    LONGS_EQUAL(-1, Sub(0, 1));
}

TEST(Sub, OneOne_ReturnZero)
{
    LONGS_EQUAL(0, Sub(1, 1));
}

TEST(Sub, ThreeFive_ReturnMinusTwo)
{
    LONGS_EQUAL(-2, Sub(3, 5));
}

#endif /* UNITTEST */
