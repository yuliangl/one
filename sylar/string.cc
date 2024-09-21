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
    const char *q = m_str;
    m_size = this->length(q);
}

String::String(const String& src){
    this->alloc();

    char *p = m_str; 
    const char* str = src.getStr();
    while((*p++= *str++) != '\0'){
    }

    const char *q = m_str;
    m_size = this->length(q);
}

String::String(String&& str) noexcept
    :m_str(str.getStr()){
        str.setStr(nullptr);
}

String::~String(){
    if(m_str)
        delete m_str;
}

String& String::operator=(const String& src){
    if(*this != src){
        char *p = m_str; 
        const char* str = src.getStr();
        while((*p++= *str++) != '\0'){
        }
        const char *q = m_str;
        m_size = this->length(q);
    }
    return *this;
}

String& String::operator=(String&& src) noexcept {
    if(*this != src){
        if(m_str)
            delete m_str;

        m_str = src.getStr();
        src.setStr(nullptr);

        const char *q = m_str;
        m_size = this->length(q);
    }
    return *this;
}

bool String::operator==(const String& src){
        const char *s = src.getStr(); 
        const char *p = m_str;

        if(m_size != src.getSize())
            return false;

        while(m_size--){
            if(*s++ != *p++)
                return false;
        }

        return true;
}

bool String::operator!=(const String& src){
    if(*this == src)
        return true;
    return false;
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
