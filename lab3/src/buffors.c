#include "buffors.h"

int get_buf_size(struct buffor* b) { return b->size; }
const char* get_buf_name(int id)
{
    if(id == BUF1) return "first buffor";
    else if (id == BUF2) return "second buffor";
    else if (id == BUF3) return "third buffor";
    else return "what is this?";
}

void init(struct buffor* b, int* memory)
{
    b->memory = memory;
    b->size = 0;
}

int push(struct buffor* b, int value)
{
    if(b->size < N)
    {
        int* place = b->memory + b->size;
        *place = value;
        ++b->size;

        return 0;
    }
    return 1;
}

int pop(struct buffor* b)
{
    int value, i;

    if(b->size > 0)
    {
        value = *b->memory;

        for(i=1; i<b->size; i++)
        {
            b->memory[i - 1] = b->memory[i];
        }
        b->size--;
        return value;
    }
    return -1;
}
