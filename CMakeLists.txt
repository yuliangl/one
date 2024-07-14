cmake_minimum_required(VERSION 3.0)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

set(LIB_SRC
    sylar/log.cc
    sylar/list.cc
    )

add_library(sylar SHARED ${LIB_SRC})

add_executable(logTest tests/logTest.cc)
add_dependencies(logTest sylar)
target_link_libraries(logTest sylar)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)



