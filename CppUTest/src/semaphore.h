#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
    int8_t posted;
} semaphore_t;

void SemaphoreInit(semaphore_t *sem);
int8_t SemaphoreTryWait(semaphore_t *sem);
int8_t SemaphorePost(semaphore_t *sem);

#ifdef __cplusplus
}
#endif

#endif
