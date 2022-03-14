# [TDD Boot - CppUTest](https://github.com/djboni/tdd-boot)

```c
/* File: example.c with additional comments. */

/* Normal source code. It is always compiled. */

#include <stdint.h>

int32_t Sum(int32_t x, int32_t y)
{
    return x + y;
}

/* Unit-test section. It is compiled only when the macro UNITTEST is defined. */

#ifdef UNITTEST
    #include "CppUTest/TestHarness.h"

TEST_GROUP (Sum)
{
    /* Test set-up: runs before each test. */
    void setup() {}

    /* Test tear-down: runs after each test. */
    void teardown() {}
};

/*
 * Test naming convention:
 *
 * - TEST(Function, Parameters_ExpectedResult) (function)
 * - TEST(Context, Interaction_ExpectedReaction) (system)
 * - TEST(Given, When_Then) (analogy to Cucumber scenarios)
 */

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

```
