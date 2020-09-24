cmake_minimum_required(VERSION 3.17)
project(AES)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(src test include ${GTEST_INCLUDE_DIRS})

add_executable(
        AES
        src/main.cpp src/utility.cpp src/utility.h src/AES.cpp src/AES.h src/Table.h src/Table.cpp
        test/test.cpp test/test.h
        include/catch.hpp
        test/tester.cpp test/tester.h)

target_link_libraries(AES ${GTEST_LIBRARIES} pthread)