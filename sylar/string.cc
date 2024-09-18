#include "string.h"

namespace sylar {


String::String(){
    this->alloc();
}

String::String(const char* str){
    this->alloc();
    char *p = m_str; 
    while((*p++= *str++) != '\0'){
    }
}

String::String(const String& src){
    this->alloc();

    char *p = m_str; 
    const char* str = src.getStr();
    while((*p++= *str++) != '\0'){
    }

}

String::String(String&& str) noexcept{
}

String::~String(){
    if(m_str)
        delete m_str;
}

String& String::operator=(const String& src){
    char *p = m_str; 
    const char* str = src.getStr();
    while((*p++= *str++) != '\0'){
    }
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
