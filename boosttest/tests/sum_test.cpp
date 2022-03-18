#include "sum.h"

#define BOOST_TEST_DYN_LINK
#include "boost/test/unit_test.hpp"

struct TestSuiteFixture
{
    /* Set-up. */
    TestSuiteFixture() {}

    /* Tear-down. */
    ~TestSuiteFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteName, TestSuiteFixture)

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

BOOST_AUTO_TEST_SUITE_END()
