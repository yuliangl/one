#include "../sylar/log.h"
#include "../sylar/list.h"

using namespace sylar;

void logTest(){
    LoggerMgr::getInstance()->init();
    int test = 1;
    printf_debug("ROOT", "part log test = %d.",test);  
    printf_debug("ROOT", "part log finash test = %d.",test);  

}

void listTest(){
    Node head(0);
    Node first(1);
    Node second(2);

    head.next = &first;
    first.prev = &head;
    first.next = &second;
    second.prev = &first;

    Node three(first);
}

int main(int argv, char** argc){
    
    logTest();


    return 0;
}
