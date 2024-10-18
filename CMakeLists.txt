cmake_minimum_required(VERSION 3.29)
project(fakepass_x)

set(CMAKE_CXX_STANDARD 17)

add_executable(fakepass_x main.cpp
        manager.cpp
        manager.hpp
        AES.cpp)
