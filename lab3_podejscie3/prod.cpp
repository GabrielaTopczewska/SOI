#include "prod.h"
// #include "definitions.h"

int producer_a(void)
{
    int value = rand() % 1000;

    while(value % 2 == 0) { value = rand() % 1000; }

    return value;
}

int producer_b(void)
{
    int value = rand() % 1000;

    while(value % 2 != 0) { value = rand() % 1000; }

    return value;
}