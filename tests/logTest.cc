#include "../sylar/log.h"

using namespace sylar;

int main(int argv, char** argc){
    
    LoggerMgr::getInstance()->init();
    int test = 1;
    printf_debug("ROOT", "part log test = %d.",test);  
    return 0;
}
