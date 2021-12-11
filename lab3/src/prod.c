#include "prod.h"
#include "definitions.h"

#include <stdlib.h>
//#include <unistd.h>

int producer_a(void)
{
    int value = rand();

    while(value % 2 == 0) { value = rand(); }

    return value;
}

int producer_b(void)
{
    int value = rand();

    while(value % 2 != 0) { value = rand(); }

    return value;
}

const char* get_name(int value)
{ return value % 2 ? "producer A" : "producer B"; }
