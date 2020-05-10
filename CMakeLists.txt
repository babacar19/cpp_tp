cmake_minimum_required(VERSION 3.15)
project(tp7)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp7
        main.cpp FileHandling.hpp FileHandling.cpp outils.hpp CIndex.h CIndex.cpp CWordStats.hpp)
