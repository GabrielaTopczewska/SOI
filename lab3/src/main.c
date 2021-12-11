#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "sem.h"
#include <time.h>
#include <stdbool.h>

int main()
{
    struct sem* s;

    if(open_all(s) == false)
    {
        printf("dupa");
        return 1;
    }

    //

    close_all(s);
    printf("niedupa");
    return 0;
}
