# [TDD Boot - CppUTest](https://github.com/djboni/tdd-boot)

```c
/* File: sum.c. */

#include "sum.h"

int32_t Sum(int32_t x, int32_t y)
{
    return x + y;
}
```

```c
/* File: sum_test.cpp with additional comments. */

#include "sum.h"

/* Include unit-test headers and fake/mocks. */
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
```

```c
/* File: main.cpp. */

#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, char **argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
```
