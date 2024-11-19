#ifndef _THREAD_H_
#define _THREAD_H_

#include <memory>
#include <vector>
#include <string>
#include <functional>

#include "log.h"


namespace sylar {


class Thread {
public:
    typedef std::shared_ptr<Thread> ptr;
    Thread(string name, std::function<void()> cb);
    Thread(Thread& ) = delete;
    THread(Thread&& ) = delete;
    Thread& operator=(Thread&) = delete;

    ~Thread();
private:
    pthread_t* m_pt;
    string m_name;
    pid_t m_pid;
    std::function<void()> m_callback;
};








}; // end namespace

#endif
