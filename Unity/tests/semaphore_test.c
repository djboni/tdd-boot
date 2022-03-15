#include "semaphore.h"

#include "unity.h"

semaphore_t sem;

void suiteSetUp(void)
{
}

int suiteTearDown(int num_failures)
{
    return num_failures;
}

void setUp(void)
{
    SemaphoreInit(&sem);
}

void tearDown(void)
{
}

void test_Semaphore_Post_SuccessOneWhenNotPosted(void)
{
    TEST_ASSERT_EQUAL(1, SemaphorePost(&sem));
}

void test_Semaphore_Post_FailZeroWhenPostedTwice(void)
{
    SemaphorePost(&sem);
    TEST_ASSERT_EQUAL(0, SemaphorePost(&sem));
}

void test_Semaphore_TryWait_FailZeroWhenNotPosted(void)
{
    TEST_ASSERT_EQUAL(0, SemaphoreTryWait(&sem));
}

void test_Semaphore_TryWait_SuccessOneWhenPosted(void)
{
    SemaphorePost(&sem);
    TEST_ASSERT_EQUAL(1, SemaphoreTryWait(&sem));
}
