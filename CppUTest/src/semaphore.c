#include "semaphore.h"

void SemaphoreInit(semaphore_t *sem)
{
    sem->posted = 0;
}

int8_t SemaphoreTryWait(semaphore_t *sem)
{
    if (!sem->posted)
        return 0;
    sem->posted = 0;
    return 1;
}

int8_t SemaphorePost(semaphore_t *sem)
{
    if (sem->posted)
        return 0;
    sem->posted = 1;
    return 1;
}

#ifdef UNITTEST
    #include "CppUTest/TestHarness.h"

TEST_GROUP (Semaphore)
{
    semaphore_t sem;

    void setup() { SemaphoreInit(&sem); }
    void teardown() {}
};

TEST(Semaphore, Post_SuccessOneWhenNotPosted)
{
    LONGS_EQUAL(1, SemaphorePost(&sem));
}

TEST(Semaphore, Post_FailZeroWhenPostedTwice)
{
    SemaphorePost(&sem);
    LONGS_EQUAL(0, SemaphorePost(&sem));
}

TEST(Semaphore, TryWait_FailZeroWhenNotPosted)
{
    LONGS_EQUAL(0, SemaphoreTryWait(&sem));
}

TEST(Semaphore, TryWait_SuccessOneWhenPosted)
{
    SemaphorePost(&sem);
    LONGS_EQUAL(1, SemaphoreTryWait(&sem));
}

#endif /* UNITTEST */
