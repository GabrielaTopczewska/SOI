#include <queue>
//#include <pthread.h>
#include <thread>
#include "buffer.h"
#include "prod_cons.h"

Buffer* buf1;        // even
Buffer* buf2;        // odd
Buffer* buf3;        // mixed

void producer(int type)
{
    int value1, value2;
    while(1)
    {
        switch(type){
            case 0:
                value1 = producer_a();
                value2 = producer_a();
                buf1->produce(value1);
                buf3->produce(value2);
                break;
            case 1:
                value1 = producer_b();
                value2 = producer_b();
                buf2->produce(value1);
                buf3->produce(value2);
                break;
            default:
                printf("producent %d padł", type);
                exit(EXIT_FAILURE);
        }
    }
}

void consumer(int type)
{
    while(1){
        switch (type)
        {
            case 0:
                buf1->consume();
                break;
            case 1:
                buf2->consume();
                break;
            case 2:
                buf3->consume();
                break;
            default:
                printf("konsument %d padł", type);
                exit(EXIT_FAILURE);
        }
    }
}

int main()
{
    srand(time(NULL));

    buf1 = new Buffer(0);
    buf2 = new Buffer(1);
    buf3 = new Buffer(2);

    std::thread p1(producer, 0);
    std::thread p2(producer, 1);
    std::thread c1(consumer, 0);
    std::thread c2(consumer, 1);
    std::thread c3(consumer, 2);

    p1.join();
    p2.join();
    c1.join();
    c2.join();
    c3.join();

    return 0;
}