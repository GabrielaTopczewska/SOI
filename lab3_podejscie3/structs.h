#ifndef STR_H
#define STR_H

#include "definitions.h"
#include "semaphore.h"

struct kolejka {
    int idx;                //gdzie wstawic
    int arr[QUEUE_MAX_SIZE];
};

struct dane_procesow
{
    int shm_odd_desc;
    kolejka *q_odd;
    sem_t* sem_odd;
    sem_t* odd_emp;
    sem_t* odd_full;

    int shm_even_desc;
    kolejka *q_even;
    sem_t* sem_even;
    sem_t* even_emp;
    sem_t* even_full;

    int shm_mixed_desc;
    kolejka *q_mixed;
    sem_t* sem_mixed;
    sem_t* mix_emp;
    sem_t* mix_full;
};

#endif