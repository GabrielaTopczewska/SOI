#ifndef BUF_H
#define BUF_H

#define N 10

#include "monitor.h"
#include <queue>

class Buffer : public Monitor
{
    public:
    Buffer(int name_);
    void produce(int value);
    void consume();

    private:
    std::queue<int> queue_;
    Condition full;
    Condition empty;
    int count;
    int name;
};

#endif