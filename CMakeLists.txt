# cmake_minimum_required(VERSION <specify CMake version here>)
project(spamfilter C)

set(CMAKE_C_STANDARD 99)

add_executable(spamfilter filter_main.c classifier.c)