#include "string.h"

namespace sylar {


String::String(){
    this->alloc();
}

String::String(const char* str){
    this->alloc();
    int index = 0;
    while(*str != '\0'){
        m_str[index] = *str++;
        ++index;
    }
    m_str[index] = *str;
}

String::String(const String& src){
    this->alloc();

    const char* str = src.getStr();
    std::cout << "copy: " << str << std::endl;
    int index = 0;
    while(*str != '\0'){
        m_str[index] = *str++;
        ++index;
    }
    m_str[index] = *str;

    std::cout << "copyend: " << str << std::endl;
}

String::String(String&& str) noexcept{
}

String::~String(){
    if(m_str)
        delete m_str;
}

String& String::operator=(const String& src){
    const char* str = src.getStr();
    int index = 0;
    while(*str != '\0'){
        m_str[index] = *str++;
        ++index;
    }
    m_str[index] = *str;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& str){
    os << str.getStr();
    return os;
}

void String::alloc(){
    m_str = new char[m_capacity];
}


int String::length(const char* src){
    int length = 0;
    while(*src++ != '\0'){
        ++length;
    }
    return length;
}
































};
