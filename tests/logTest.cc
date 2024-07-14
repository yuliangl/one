#include "../sylar/log.h"
#include "../sylar/list.h"

using namespace sylar;

int main(int argv, char** argc){
    
    LoggerMgr::getInstance()->init();
    int test = 1;
    printf_debug("ROOT", "part log test = %d.",test);  

    Node head(0);
    Node first(1);
    Node second(2);

    head.next = &first;
    first.prev = &head;
    first.next = &second;
    second.prev = &first;

    Node three(first);

    printf_debug("ROOT", "part log finash test = %d.",test);  
    return 0;
}
