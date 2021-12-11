#ifndef BUF_H
#define BUF_H

#include "definitions.h"
#include <stdlib.h>

struct buffor
{
    int* memory;
    int size;
};

int get_size(struct buffor* b);
const char* get_name(int id);

void init(struct buffor* b, int* mem);
int push(struct buffor* b, int value);
int pop(struct buffor* b);

#endif