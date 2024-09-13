#ifndef _STRING_H_
#define _STRING_H_

namespace sylar {



class String {
public:
    String();
    String(const char*);
    String(const String& str);
    String(String&& str) noexcept;
    ~String();

    String& operator=(const String& str);

    void alloc();

private:
    char* m_str;
    
};














































};//sylr





















































#endif
