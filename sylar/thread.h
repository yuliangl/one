#ifndef _THREAD_H_
#define _THREAD_H_

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <pthread.h>

#include "log.h"


namespace sylar {


class Thread {
public:
    typedef std::shared_ptr<Thread> ptr;
    Thread(std::function<void()> cb, std::string& name);
    Thread(Thread& ) = delete;
    THread(Thread&& ) = delete;
    Thread& operator=(Thread&) = delete;

    ~Thread();

    int join();
    int detach();

    const std::string& getName() const {return m_name;}
    static Thread* GetThis(); // get current thread pointer
    static std::string& GetName(); // get current thread name
    static void SetName(const std::string& name);
private:
    static void* run(void* arg);
    
    pthread_t m_pt = 0;// thread_t
    string m_name; // thread name
    pid_t m_pid = -1; // thread id 
    std::function<void()> m_callback;
};








}; // end namespace

#endif
