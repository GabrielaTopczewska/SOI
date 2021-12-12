#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <semaphore.h>
#include <queue>

#include "definitions.h"
#include "prod.h"

using namespace std;

queue <int> buf1;
queue <int> buf2;
queue <int> buf3;

sem_t mut1;
sem_t mut2;
sem_t mut3;
sem_t emp1;
sem_t emp2;
sem_t emp3;
sem_t ful1;
sem_t ful2;
sem_t ful3;


void init_sem() {
    sem_init(&mut1, PSHARED, MUT_VAL);
    sem_init(&ful1, PSHARED, FULL_VAL);
    sem_init(&emp1, PSHARED, N);

    sem_init(&mut2, PSHARED, MUT_VAL);
    sem_init(&ful2, PSHARED, FULL_VAL);
    sem_init(&emp2, PSHARED, N);

    sem_init(&mut3, PSHARED, MUT_VAL);
    sem_init(&ful3, PSHARED, FULL_VAL);
    sem_init(&emp3, PSHARED, N);
}

void destroy_sem()
{
    sem_destroy(&mut1);
    sem_destroy(&mut2);
    sem_destroy(&mut3);

    sem_destroy(&emp1);
    sem_destroy(&emp2);
    sem_destroy(&emp3);

    sem_destroy(&ful1);
    sem_destroy(&ful2);
    sem_destroy(&ful3);
}

void* producer_routine(void* arg)
{
    int value;
    for(int i=0; i < MAX_DATA; i++)
    {
        // cout << "dupa" << endl;

        sem_wait(((struct arguments*)arg)->empty);
        sem_wait(((struct arguments*)arg)->mutex);

        // cout << "dupa" << endl;

        switch (((struct arguments*)arg)->id)
        {
            case 0:
                value = producer_a();
                buf1.push(value);
                break;
            case 1:
                value = producer_b();
                buf2.push(value);
                break;
            default:
                cout << "Gowno nie producent";
                value = -1;
                break;
        }
        // sleep(1);

        sem_post(((struct arguments*)arg)->mutex);
        sem_post(((struct arguments*)arg)->full);
    }
    printf("koniec produc");
    free(arg);
    pthread_exit(NULL);
}

void* consumer_routine(void* arg)
{
    int value;
    int id = *(int*)arg;
    for(int i=0; i < MAX_DATA; i++)
    {
        // cout << "dupa" << endl;
        switch (((struct arguments*)arg)->id)
        {
        case 0:
            sem_wait(((struct arguments*)arg)->full);
            sem_wait(((struct arguments*)arg)->mutex);
            value = buf1.front();
            cout << "value from buf1 is " << value << endl;
            buf1.pop();
            sem_post(((struct arguments*)arg)->mutex);
            sem_post(((struct arguments*)arg)->empty);
            break;
        case 1:
            sem_wait(((struct arguments*)arg)->full);
            sem_wait(((struct arguments*)arg)->mutex);
            value = buf2.front();
            cout << "value from buf2 is " << value << endl;
            buf2.pop();
            sem_post(((struct arguments*)arg)->mutex);
            sem_post(((struct arguments*)arg)->empty);
            break;
        case 2:
            sem_wait(((struct arguments*)arg)->full);
            sem_wait(((struct arguments*)arg)->mutex);
            value = buf3.front();
            cout << "value from buf3 is " << value << endl;
            buf3.pop();
            sem_post(((struct arguments*)arg)->mutex);
            sem_post(((struct arguments*)arg)->empty);
            break;
        default:
            cout << "Gowno nie konsument";
            break;
        }
    }
    printf("koniec konsum");
    free(arg);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    pthread_t threads[PROCS-3];

    init_sem();

    struct arguments* a = (struct arguments *)malloc(sizeof(struct arguments));
    a->id = 0;
    a->id_buf = BUF1;
    a->mutex = &mut1;
    a->empty = &emp1;
    a->full = &ful1;

    struct arguments* b = (struct arguments *)malloc(sizeof(struct arguments));
    b->id = 1;
    b->id_buf = BUF2;
    b->mutex = &mut2;
    b->empty = &emp2;
    b->full = &ful2;

    // int* c = (int *)malloc(sizeof(int));
    // *c = BUF1;
    // int* d = (int *)malloc(sizeof(int));
    // *d = BUF2;
    // int* e = (int *)malloc(sizeof(int));
    // *e = BUF3;

    pthread_create(&threads[0], NULL, &producer_routine, (void *)b);
    // pthread_create(&threads[1], NULL, &producer_routine, (void *)b);
    pthread_create(&threads[2], NULL, &consumer_routine, (void *)b);
    // pthread_create(&threads[3], NULL, &consumer_routine, (void *)b);
    // pthread_create(&threads[4], NULL, &consumer_routine, NULL);

    for(int i=0; i<PROCS-3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    destroy_sem();

    return 0;
}