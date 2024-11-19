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
    String& operator=(String&& src) noexcept;
    bool operator==(const String& src);
    bool operator!=(const String& src);
    char& operator[](std::size_t n);
    const char& operator[](std::size_t n) const;
    friend String operator+(String& lhs, String& rhs);
    friend std::ostream& operator<<(std::ostream& os, const String& str);


    void swap(String& rhs);
    char* getStr() const {return m_str;}
    int getSize() const {return m_size;}
    void setStr(char * src) {m_str = src;}

private:
    void alloc();
    int length(const char* src);

    char* m_str;
    int m_size = 0;
    int m_capacity = 100;
    
};














































};//sylr





















































#endif
