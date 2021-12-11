#ifndef SEM_H
#define SEM_H

#include "definitions.h"
#include <stdbool.h>
#include <semaphore.h>


struct sem
{
    sem_t* mutexes[3];
    sem_t* emptys[3];
    sem_t* fulls[3]
};

bool open_mutex(struct sem* semap, set_t* semap, const char* name, int index);
bool open_empty(struct sem* semap, set_t* semap, const char* name, int index);
bool open_full(struct sem* semap, set_t* semap, const char* name, int index);

bool open(struct sem* semap);
void close(struct sem* semap);

#endif