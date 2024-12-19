#include "thread.h"



namespace sylar {

static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_threadName = "UNKNOW";


Thread* Thread::GetThis() {
    return t_thread;
}

std::string& Thread::GetName() {
    return t_threadName;
}

void Thread::SetName(const std::string& name) {
    t_threadName = name;
}



Thread::Thread(std::function<void()> cb, std::string& name)
    :m_name(name)
    ,m_callback(cb)
{
    int rv = pthread_create(&m_pid, nullptr, &Thread::run, this);    
}
Thread::~Thread(){
    int rv = pthread_cancel(m_pt);
}

int Thread::join(){
    int rv =  pthread_join(m_pt, nullptr);
}
int Thread::detach(){
    int rv =  pthread_detach(m_pt); 
}


void* Thread::run(void* arg){
    Thread* thread = (Thread*)arg;
    t_thread = thread;
    t_threadName = thread->m_name;
    thread->m_pid = pthread_self();

    pthread_setname_np(pthread_self(), t_threadName.c_str());

    std::function<void()> cb;
    cb.swap(thread->m_callback);

    cb();

    return 0;

}












}; // end namespace
