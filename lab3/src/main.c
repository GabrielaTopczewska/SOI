#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "sem.h"
#include <time.h>
#include <stdbool.h>

int main()
{
    sem* semap;
    if(open(semap) == false)
    {
        printf("dupa");
        return 1;
    }

    //

    close(semap);
    printf("niedupa");
    return 0;
}
