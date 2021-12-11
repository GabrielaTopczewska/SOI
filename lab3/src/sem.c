#include "sem.h"


bool open_mutex(struct sem* s, set_t* semap, const char* name, int index)
{
    semap = sem_open(name, O_CREAT | O_EXCL);
    if(semap != SEM_FAILED) s->mutexes[index] = semap;
    else return false;
    return true;
}

bool open_empty(struct sem* s, set_t* semap, const char* name, int index)
{
    semap = sem_open(name, O_CREAT | O_EXCL);
    if(semap != SEM_FAILED) s->empty[index] = semap;
    else return false;
    return true;
}

bool open_full(struct sem* s, set_t* semap, const char* name, int index)
{
    semap = sem_open(name, O_CREAT | O_EXCL);
    if(semap != SEM_FAILED) s->fulls[index] = semap;
    else return false;
    return true;
}

bool open(struct sem* s)
{
    sem_t* semap;

    if(open_mutex(s, semap, "mutex1", 0) == false) return false;
    if(open_mutex(s, semap, "mutex2", 1) == false) return false;
    if(open_mutex(s, semap, "mutex3", 2) == false) return false;

    if(open_empty(s, semap, "empty1", 0) == false) return false;
    if(open_empty(s, semap, "empty2", 1) == false) return false;
    if(open_empty(s, semap, "empty3", 2) == false) return false;

    if(open_full(s, semap, "full1", 0) == false) return false;
    if(open_full(s, semap, "full2", 1) == false) return false;
    if(open_full(s, semap, "full3", 2) == false) return false;

    return true;        // all semaphores initialized and opened and in sem s
}

void close(struct sem* s)
{
    sem_unlink("mutex1");
    sem_unlink("mutex2");
    sem_unlink("mutex3");
    sem_unlink("empty1");
    sem_unlink("empty2");
    sem_unlink("empty3");
    sem_unlink("full1");
    sem_unlink("full2");
    sem_unlink("full3");

    for(int i=0; i<3; i++)
    {
        sem_close(s->mutexes[i]);
        sem_close(s->emptys[i]);
        sem_close(s->fulls[i]);
    }
}
