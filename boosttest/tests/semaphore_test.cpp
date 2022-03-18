#include "semaphore.h"

#define BOOST_TEST_DYN_LINK
#include "boost/test/unit_test.hpp"

struct TestSuiteFixture
{
    semaphore_t sem;

    /* Set-up. */
    TestSuiteFixture() { SemaphoreInit(&sem); }

    /* Tear-down. */
    ~TestSuiteFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteName, TestSuiteFixture)

BOOST_AUTO_TEST_CASE(Post_SuccessOneWhenNotPosted)
{
    BOOST_TEST(1 == SemaphorePost(&sem));
}

BOOST_AUTO_TEST_CASE(Post_FailZeroWhenPostedTwice)
{
    SemaphorePost(&sem);
    BOOST_TEST(0 == SemaphorePost(&sem));
}

BOOST_AUTO_TEST_CASE(TryWait_FailZeroWhenNotPosted)
{
    BOOST_TEST(0 == SemaphoreTryWait(&sem));
}

BOOST_AUTO_TEST_CASE(TryWait_SuccessOneWhenPosted)
{
    SemaphorePost(&sem);
    BOOST_TEST(1 == SemaphoreTryWait(&sem));
}

BOOST_AUTO_TEST_SUITE_END()
