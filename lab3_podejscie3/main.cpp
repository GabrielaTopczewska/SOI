#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "sem.h"
#include "prod.h"


void producent_work(struct dane_procesow *dane, int typ)
{
    printf("Producent [%d] rozpoczal prace [pid = %d]\n", typ, getpid());

    bool do_work1 = true;
    bool do_work2 = true;
    bool* do_work;
    char qtyp = '0';
    kolejka* qq = NULL;
    sem_t* sem = NULL;
    sem_t* emp = NULL;
    sem_t* full = NULL;

    while (do_work1 || do_work2)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == 0)         // nieparzysta lub parzysta
            {
                if (typ == 1)   // nieparzysta
                {
                    qq = dane->q_odd;
                    sem = dane->sem_odd;
                    emp = dane->odd_emp;
                    full = dane->odd_full;
                    qtyp = 'O';
                }

                if (typ == 2)   // parzysta
                {
                    qq = dane->q_even;
                    sem = dane->sem_even;
                    emp = dane->even_emp;
                    full = dane->even_full;
                    qtyp = 'E';
                }
                do_work = &do_work1;    // wskaznik na adres do_work1 (parz lub nieparz)
            }
            else                // mieszana
            {
                qq = dane->q_mixed;
                sem = dane->sem_mixed;
                emp = dane->mix_emp;
                full = dane->mix_full;
                qtyp = 'M';
                do_work = &do_work2;    // wskaznik na adres do work2 (miesz)
            }

            // sem_wait(emp);
            sem_wait(sem);
            printf("... producent [%d] pracuje z kolejka '%c' [pid = %d]\n", typ, qtyp, getpid());
            if (qq->idx == -1) qq->idx = 0;     // poczatek pracy z kolejka
            if (qq->idx < QUEUE_MAX_SIZE)
            {
                if(typ == 1){
                    qq->arr[qq->idx] = producer_a();         // tu dorobic rand
                }
                else{
                    qq->arr[qq->idx] = producer_b();
                }
                printf("... producent [%d]: Arr[%d] = %d\n", typ, qq->idx, qq->arr[qq->idx]);
                qq->idx++;
            }
            else
            {
                printf("... kolejka '%c' producenta [%d] jest pelna\n", qtyp, typ);
                *do_work = false;       //zapchal kolejke (ktoras)
                sem_post(sem);
                break;
            }
            sem_post(sem);
            // sem_post(full);

            usleep(1000 * 300 * typ);
        }
    }

    printf("Producent [%d] zakonczyl prace [pid = %d]\n", typ, getpid());
}

void konsument_work(struct dane_procesow* dane, int typ)
{
    printf("Konsument [%d] rozpoczal prace [pid = %d]\n", typ, getpid());
    kolejka* qq = NULL;
    sem_t* sem = NULL;
    sem_t* emp = NULL;
    sem_t* full = NULL;

    if (typ == 1)
    {
        qq = dane->q_odd;
        sem = dane->sem_odd;
        emp = dane->odd_emp;
        full = dane->odd_full;
    }

    if (typ == 2)
    {
        qq = dane->q_even;
        sem = dane->sem_even;
        emp = dane->even_emp;
        full = dane->even_full;
    }

    if (typ == 3)
    {
        qq = dane->q_mixed;
        sem = dane->sem_mixed;
        emp = dane->mix_emp;
        full = dane->mix_full;
    }

    bool exists = true;
    while (exists)
    {
        // sem_wait(full);
        sem_wait(sem);
        if (qq->idx > 0)        // bo jak producent wstawil to zwiekszyl na 1
        {
            int val = qq->arr[0];       // bo fifo
            printf("...... konsument [%d] pobral wartosc %d, [pid = %d]\n", typ, val, getpid());
            for (int i = 1; i <= qq->idx; i++)      // przesuwando
            {
                qq->arr[i - 1] = qq->arr[i];
            }
            qq->arr[qq->idx] = -1;      // tam juz nie ma
            qq->idx--;
        }
        else
        {
            printf("...... kolejka konsumenta [%d] jest pusta\n", typ);
            qq->idx = -1;
            exists = false;
        }
        sem_post(sem);
        // sem_post(emp);

        usleep(1000 * 1000 * typ);
    }

    printf("Konsument [%d] zakonczyl prace [pid = %d]\n", typ, getpid());
}

int main()
{
    if(QUEUE_MAX_SIZE <= 0)
    {
        printf("Queue size initialized to wrong value (0 or less).\n");
        return 0;
    }
    printf("START main().\n\n");

    int mpid = getpid();        // pid maina
    struct dane_procesow dane;  //tu trzymam dane potrzebne w trakcie dzialania procesow

    initialize_semaphores(&dane);

    //tworzenie pamieci wspoldzielonej i mapowanie
    {
        int res;

        //------------- QUEUE_ODD_NUMBER -----------------
        res = shm_open(QUEUE_ODD_NUMBER, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
        if (res == -1)
        {
            perror("Blad przy tworzeniu pamieci wspoldzielonej 'QUEUE_ODD_NUMBER'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Pamiec wspoldzielona 'QUEUE_ODD_NUMBER' utworzona.\n");
            dane.shm_odd_desc = res;

            res = ftruncate(dane.shm_odd_desc, sizeof(kolejka));
            if (res == -1)
            {
                perror("Blad przy okreslaniu rozmiaru pamieci wspoldzielonej 'QUEUE_ODD_NUMBER'");
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("Rozmiar pamieci wspoldzielonej 'QUEUE_ODD_NUMBER' okreslony (%d).\n", sizeof(kolejka));

                kolejka* result = (kolejka*)mmap(NULL, sizeof(kolejka), PROT_READ | PROT_WRITE, MAP_SHARED, dane.shm_odd_desc, 0);
                if (result == (void*)(-1))
                {
                    perror("Blad przy okreslaniu rozmiaru pamieci wspoldzielonej 'QUEUE_ODD_NUMBER'");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("Mapowanie pamieci wspoldzielonej 'QUEUE_ODD_NUMBER' prawidlowe.\n");
                    dane.q_odd = result;        // wskaznik na kolejke (obszar sformatowany jak kolejka)
                    dane.q_odd->idx = -1;       // jeszcze nieuzywana kolejka (etap tworzenia)
                }
            }
        }

        //------------- QUEUE_EVEN_NUMBER -----------------
        res = shm_open(QUEUE_EVEN_NUMBER, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
        if (res == -1)
        {
            perror("Blad przy tworzeniu pamieci wspoldzielonej 'QUEUE_EVEN_NUMBER'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Pamiec wspoldzielona 'QUEUE_EVEN_NUMBER' utworzona.\n");
            dane.shm_even_desc = res;

            res = ftruncate(dane.shm_even_desc, sizeof(kolejka));
            if (res == -1)
            {
                perror("Blad przy okreslaniu rozmiaru pamieci wspoldzielonej 'QUEUE_EVEN_NUMBER'");
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("Rozmiar pamieci wspoldzielonej 'QUEUE_EVEN_NUMBER' okreslony (%d).\n", sizeof(kolejka));

                kolejka* result = (kolejka*)mmap(NULL, sizeof(kolejka), PROT_READ | PROT_WRITE, MAP_SHARED, dane.shm_even_desc, 0);
                if (result == (void*)(-1))
                {
                    perror("Blad przy okreslaniu rozmiaru pamieci wspoldzielonej 'QUEUE_EVEN_NUMBER'");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("Mapowanie pamieci wspoldzielonej 'QUEUE_EVEN_NUMBER' prawidlowe.\n");
                    dane.q_even = result;
                    dane.q_even->idx = -1;
                }
            }
        }

        //------------- QUEUE_MIXED_NUMBER -----------------
        res = shm_open(QUEUE_MIXED_NUMBER, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
        if (res == -1)
        {
            perror("Blad przy tworzeniu pamieci wspoldzielonej 'QUEUE_MIXED_NUMBER'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Pamiec wspoldzielona 'QUEUE_MIXED_NUMBER' utworzona.\n");
            dane.shm_mixed_desc = res;

            res = ftruncate(dane.shm_mixed_desc, sizeof(kolejka));
            if (res == -1)
            {
                perror("Blad przy okreslaniu rozmiaru pamieci wspoldzielonej 'QUEUE_MIXED_NUMBER'");
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("Rozmiar pamieci wspoldzielonej 'QUEUE_MIXED_NUMBER' okreslony (%d).\n", sizeof(kolejka));

                kolejka* result = (kolejka*)mmap(NULL, sizeof(kolejka), PROT_READ | PROT_WRITE, MAP_SHARED, dane.shm_mixed_desc, 0);
                if (result == (void*)(-1))
                {
                    perror("Blad przy okreslaniu rozmiaru pamieci wspoldzielonej 'QUEUE_MIXED_NUMBER'");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("Mapowanie pamieci wspoldzielonej 'QUEUE_MIXED_NUMBER' prawidlowe.\n");
                    dane.q_mixed = result;
                    dane.q_mixed->idx = -1;
                }
            }
        }
    }

    //tworzenie procesow
    {
        int pid = fork(); //producent 1
        if (pid == 0)       // 0 jesli to dziecko
        {
            producent_work(&dane,1);
        }
        else if (pid < 0) //blad
        {
            printf("Tworzenie procesu producenta 1 potomnego nieudane!");
            return 0;
        }
        else //jestem w procesie rodzica
        {
            pid = fork(); //producent 2
            if (pid == 0) //czyli je�eli jestem w procesie potomnym
            {
                producent_work(&dane, 2);
            }
            else if (pid < 0) //tutaj proces rodzica
            {
                printf("Tworzenie procesu producenta 2 potomnego nieudane!");
                return 0;
            }
            else
            {
                usleep(1000 * 1000);

                pid = fork(); //konsument 1
                if (pid == 0) //czyli je�eli jestem w procesie potomnym
                {
                    konsument_work(&dane, 1);
                }
                else if (pid < 0)
                {
                    printf("Tworzenie procesu konsumenta 1 potomnego nieudane!");
                    return 0;
                }
                else
                {
                    usleep(1000 * 1500);

                    pid = fork(); //konsument 2
                    if (pid == 0) //czyli je�eli jestem w procesie potomnym
                    {
                        konsument_work(&dane, 2);
                    }
                    else if (pid < 0)
                    {
                        printf("Tworzenie procesu konsumenta 2 potomnego nieudane!");
                        return 0;
                    }
                    else
                    {
                        usleep(1000 * 2000);

                        pid = fork(); //konnsument 3
                        if (pid == 0) //czyli je�eli jestem w procesie potomnym
                        {
                            konsument_work(&dane, 3);
                        }
                        else if (pid < 0)
                        {
                            printf("Tworzenie procesu konsumenta 1 potomnego nieudane!");
                            return 0;
                        }
                    }
                }
            }
        }
    }

    while (wait(NULL) > 0);         // proces maina wisi i czeka na potomne az sie skoncza

    if (mpid == getpid())
    {
        printf("\n KOLEJKA 'O':\n");
        for (int i = 0; i < dane.q_odd->idx; i++)
        {
            printf("[%d] ",dane.q_odd->arr[i]);
        }

        printf("\n KOLEJKA 'E':\n");
        for (int i = 0; i < dane.q_even->idx; i++)
        {
            printf("[%d] ", dane.q_even->arr[i]);
        }

        printf("\n KOLEJKA 'M':\n");
        for (int i = 0; i < dane.q_mixed->idx; i++)
        {
            printf("[%d] ", dane.q_mixed->arr[i]);
        }
        printf("\nCzyszcze zasoby...\n");

        //czyszcze zasoby
        munmap(dane.q_odd, sizeof(kolejka));
        shm_unlink(QUEUE_ODD_NUMBER);
        sem_unlink(SEM_ODD_NUMBER);
        sem_close(dane.sem_odd);

        munmap(dane.q_even, sizeof(kolejka));
        shm_unlink(QUEUE_EVEN_NUMBER);
        sem_unlink(SEM_EVEN_NUMBER);
        sem_close(dane.sem_even);

        munmap(dane.q_mixed, sizeof(kolejka));
        shm_unlink(QUEUE_MIXED_NUMBER);
        sem_unlink(SEM_MIXED_NUMBER);
        sem_close(dane.sem_mixed);

        printf("END main().\n");
    }
    return 0;
}