# [TDD Boot - Boost.Test](https://github.com/djboni/tdd-boot)

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
#define BOOST_TEST_DYN_LINK
#include "boost/test/unit_test.hpp"

struct TestSuiteFixture
{
    /* Test set-up: runs before each test. */
    TestSuiteFixture() {}

    /* Test tear-down: runs after each test. */
    ~TestSuiteFixture() {}
};

/* Start of test suite. */
BOOST_FIXTURE_TEST_SUITE(TestSuiteName, TestSuiteFixture)

/*
 * Test naming convention:
 *
 * - test_Function_Parameters_ExpectedResult (function)
 * - test_Context_Interaction_ExpectedReaction (system)
 * - test_Given_When_Then (analogy to Cucumber scenarios)
 */

BOOST_AUTO_TEST_CASE(ZeroZero_ReturnZero)
{
    BOOST_TEST(0 == Sum(0, 0));
}

BOOST_AUTO_TEST_CASE(OneZero_ReturnOne)
{
    BOOST_TEST(1 == Sum(1, 0));
}

BOOST_AUTO_TEST_CASE(ZeroOne_ReturnOne)
{
    BOOST_TEST(1 == Sum(0, 1));
}

BOOST_AUTO_TEST_CASE(OneOne_ReturnTwo)
{
    BOOST_TEST(2 == Sum(1, 1));
}

BOOST_AUTO_TEST_CASE(ThreeFive_ReturnEight)
{
    BOOST_TEST(8 == Sum(3, 5));
}

/* End of test suite. */
BOOST_AUTO_TEST_SUITE_END()
```

```c
/* File: main.cpp. */

#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include "boost/test/unit_test.hpp"
```
