#include "filesystem.h"

int main(){
    run = 1;
    while(run) interface();
    std::cout << "File system closed." << std::endl;


    std::cout << sizeof(superBlock) << std::endl;
    std::cout << sizeof(iNode) << std::endl;
    std::cout << sizeof(dataBlock) << std::endl;
    return 0;
}