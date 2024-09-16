#include <iostream>
#include "../sylar/log.h"
#include "../sylar/list.h"
#include "../sylar/string.h"

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

void stringTest(){
    String strFirst("first");
    String strSecond(strFirst);
    String strThird = strSecond;

    std::cout << "first: " << strFirst << std::endl;
    std::cout << "second: " << strSecond << std::endl;
    std::cout << "third: " << strThird << std::endl;
}

int main(int argv, char** argc){
    
    logTest();
    stringTest();


    return 0;
}
