#include "thread.h"



namespace sylar {

static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_threadName = "UNKNOW";


Thread* Thread::GetThis() {
    return t_thread;
}

std::string& Thread::GetName() {
    return t_name;
}

void Thread::SetName(const std::string& name) {
    t_threadName = name;
}



Thread::Thread(std::function<void()> cb, std::string& name)
    :m_name(name)
    ,m_callback(cb)
{
    
}
Thread::~Thread();

int join();
int detach();

const std::string& getName() const {return m_name;}













}; // end namespace
