#include <iostream>
#include <thread>
#include "Thread_pool/Thread_pool.h"
void test1(){
    std::cout << "Привет Денис";
}
void test2(){
    std::cout << "Привет Вася";
}
int main() {
    Thread_pool thrPl;
    for(auto i = 0; i < 5; i++){
        thrPl.submit(test1);
        thrPl.submit(test2);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));

    }
    return 0;
}
