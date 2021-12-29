#include <buffer.h>
#include <prod_cons.h>

Buffer::Buffer()
{

}

void Buffer::produce(int value){
    enter();
    if(count == N) wait(full);

    queue_.push(value);
    count++;
    if(count == 1) signal(empty);
    leave();
}

void Buffer::consume(){
    enter();
    if(count == 0) wait(empty);

    printf("Item popped: %d", queue_.front());
    queue_.pop();
    count--;
    if(count == N-1) signal(full);
    leave();
}
