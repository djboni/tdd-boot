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
