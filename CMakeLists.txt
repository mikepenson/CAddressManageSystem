cmake_minimum_required(VERSION 3.5)
project(address)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES address.c address.c)
add_executable(address ${SOURCE_FILES})