#ifndef PROD_H
#define PROD_H

#include <semaphore.h>
#include <queue>

struct arguments
{
    int id;
    int id_buf;
    sem_t* mutex;
    sem_t* empty;
    sem_t* full;
};

int producer_a(void);
int producer_b(void);

const char* get_name(int value);

#endif