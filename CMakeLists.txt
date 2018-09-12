# cmake_minimum_required(VERSION <specify CMake version here>)
project(spamfilter C)

set(CMAKE_C_STANDARD 99)

add_executable(spamfilter trainer/trainer_main.c spamfilter.h)