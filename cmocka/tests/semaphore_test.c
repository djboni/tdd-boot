#include "semaphore.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "cmocka.h"

semaphore_t sem;

int suiteSetUp(void **state)
{
    (void)state;
    return 0;
}

int suiteTearDown(void **state)
{
    (void)state;
    return 0;
}

int setUp(void **state)
{
    (void)state;

    SemaphoreInit(&sem);

    return 0;
}

int tearDown(void **state)
{
    (void)state;
    return 0;
}

void test_Semaphore_Post_SuccessOneWhenNotPosted(void **state)
{
    (void)state;

    assert_int_equal(1, SemaphorePost(&sem));
}

void test_Semaphore_Post_FailZeroWhenPostedTwice(void **state)
{
    (void)state;

    SemaphorePost(&sem);
    assert_int_equal(0, SemaphorePost(&sem));
}

void test_Semaphore_TryWait_FailZeroWhenNotPosted(void **state)
{
    (void)state;

    assert_int_equal(0, SemaphoreTryWait(&sem));
}

void test_Semaphore_TryWait_SuccessOneWhenPosted(void **state)
{
    (void)state;

    SemaphorePost(&sem);
    assert_int_equal(1, SemaphoreTryWait(&sem));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(
            test_Semaphore_Post_SuccessOneWhenNotPosted, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Semaphore_Post_FailZeroWhenPostedTwice, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Semaphore_TryWait_FailZeroWhenNotPosted, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Semaphore_TryWait_SuccessOneWhenPosted, setUp, tearDown),
    };

    return cmocka_run_group_tests(tests, suiteSetUp, suiteTearDown);
}
