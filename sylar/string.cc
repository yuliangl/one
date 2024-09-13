#include "string.h"

namespace sylar {


String::String(){
}
String::String(const char*){
}
String::String(const String& str){
}
String::String(String&& str) noexcept{
}
String::~String(){
    if(m_str)
        delete m_str;
}

String& String::operator=(const String& str){
}

void String::alloc(){
    m_str = new char[100];
}
};
