#include "buffer.h"
#include "prod_cons.h"

Buffer::Buffer(int name_)
{
    name = name_;
    count = 0;
    //full
    //empty
    //queue
}

void Buffer::produce(int value){
    enter();
    if(count == N) wait(full);

    queue_.push(value);
    printf("Item %d pushed to queue %d\n", value, name);

    usleep(1000*1000);

    count++;
    if(count == 1) signal(empty);
    leave();
}

void Buffer::consume(){
    enter();
    if(count == 0) wait(empty);

    printf("Item popped: %d from queue %d\n", queue_.front(), name);
    queue_.pop();

    usleep(1000*1000);

    count--;
    if(count == N-1) signal(full);
    leave();
}
