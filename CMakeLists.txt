cmake_minimum_required(VERSION 3.17)
project(AES)

set(CMAKE_CXX_STANDARD 14)

include_directories(src test)

add_executable(
        AES
        src/main.cpp src/utility.cpp src/utility.h src/AES.cpp src/AES.h src/Table.h src/Table.cpp
        test/test.cpp test/test.h test/catch.hpp)