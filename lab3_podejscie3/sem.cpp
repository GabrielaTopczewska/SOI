#include "sem.h"

void initialize_semaphores(dane_procesow *dane)
    {
        sem_t* res_sem;

        //------------ SEM_ODD_NUMBER ------------------
        sem_unlink(SEM_ODD_NUMBER);
        sem_close(dane->sem_odd);

        res_sem = sem_open(SEM_ODD_NUMBER, O_CREAT | O_EXCL, 0666, 1);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_ODD_NUMBER'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_ODD_NUMBER' utworzony.\n");
            dane->sem_odd = res_sem;
        }
        //------------ SEM_EVEN_NUMBER ------------------
        sem_unlink(SEM_EVEN_NUMBER);
        sem_close(dane->sem_even);

        res_sem = sem_open(SEM_EVEN_NUMBER, O_CREAT | O_EXCL, 0666, 1);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_EVEN_NUMBER'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_EVEN_NUMBER' utworzony.\n");
            dane->sem_even = res_sem;
        }
        //------------ SEM_MIXED_NUMBER ------------------
        sem_unlink(SEM_MIXED_NUMBER);
        sem_close(dane->sem_mixed);

        res_sem = sem_open(SEM_MIXED_NUMBER, O_CREAT | O_EXCL, 0666, 1);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_MIXED_NUMBER'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_MIXED_NUMBER' utworzony.\n");
            dane->sem_mixed = res_sem;
        }

        // odd emp
        sem_unlink(SEM_ODD_EMP);
        sem_close(dane->odd_emp);

        res_sem = sem_open(SEM_ODD_EMP, O_CREAT | O_EXCL, 0666, QUEUE_MAX_SIZE);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_ODD_EMP'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_ODD_EMP' utworzony.\n");
            dane->odd_emp = res_sem;
        }

        // even emp
        sem_unlink(SEM_EVEN_EMP);
        sem_close(dane->even_emp);

        res_sem = sem_open(SEM_EVEN_EMP, O_CREAT | O_EXCL, 0666, QUEUE_MAX_SIZE);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_EVEN_EMP'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_EVEN_EMP' utworzony.\n");
            dane->odd_emp = res_sem;
        }

        // mix emp
        sem_unlink(SEM_MIXED_EMP);
        sem_close(dane->mix_emp);

        res_sem = sem_open(SEM_MIXED_EMP, O_CREAT | O_EXCL, 0666, QUEUE_MAX_SIZE);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_MIXED_EMP'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_MIXED_EMP' utworzony.\n");
            dane->mix_emp = res_sem;
        }

        // odd full
        sem_unlink(SEM_ODD_FULL);
        sem_close(dane->odd_full);

        res_sem = sem_open(SEM_ODD_FULL, O_CREAT | O_EXCL, 0666, 0);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_ODD_FULL'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_ODD_FULL' utworzony.\n");
            dane->odd_full = res_sem;
        }


            // even full
        sem_unlink(SEM_EVEN_FULL);
        sem_close(dane->even_full);

        res_sem = sem_open(SEM_EVEN_FULL, O_CREAT | O_EXCL, 0666, 0);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_EVEN_FULL'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_EVEN_FULL' utworzony.\n");
            dane->even_full = res_sem;
        }

            // mix full
        sem_unlink(SEM_MIXED_FULL);
        sem_close(dane->mix_full);

        res_sem = sem_open(SEM_MIXED_FULL, O_CREAT | O_EXCL, 0666, 0);
        if (res_sem == SEM_FAILED)
        {
            perror("Blad przy tworzeniu semafora 'SEM_MIXED_FULL'");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Semafor 'SEM_MIXED_FULL' utworzony.\n");
            dane->mix_full = res_sem;
        }

    }

void close_semaphores(dane_procesow *dane)
{
        sem_unlink(SEM_ODD_NUMBER);
        sem_close(dane->sem_odd);
        sem_unlink(SEM_ODD_EMP);
        sem_close(dane->odd_emp);
        sem_unlink(SEM_ODD_FULL);
        sem_close(dane->odd_full);

        sem_unlink(SEM_EVEN_NUMBER);
        sem_close(dane->sem_even);
        sem_unlink(SEM_EVEN_EMP);
        sem_close(dane->even_emp);
        sem_unlink(SEM_EVEN_FULL);
        sem_close(dane->even_full);

        sem_unlink(SEM_MIXED_NUMBER);
        sem_close(dane->sem_mixed);
        sem_unlink(SEM_MIXED_EMP);
        sem_close(dane->mix_emp);
        sem_unlink(SEM_MIXED_FULL);
        sem_close(dane->mix_full);
}
