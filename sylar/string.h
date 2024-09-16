#ifndef _STRING_H_
#define _STRING_H_

#include <iostream>

namespace sylar {



class String {
public:
    String();
    String(const char*);
    String(const String& src);
    String(String&& str) noexcept;
    ~String();

    String& operator=(const String& src);
    friend std::ostream& operator<<(std::ostream& os, const String& str);


    void alloc();
    int length(const char* src);
    const char* getStr() const {return m_str;}

private:
    char* m_str;
    int m_capacity = 100;
    
};














































};//sylr





















































#endif
