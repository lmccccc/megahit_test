cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp kmer.cpp read.cpp common_functions.h defination.h common_functions.cpp main_functions.h main_funcitons.cpp succinctDBG.cpp succinctDBG.h rank_list.cpp rank_list.h select_list.cpp select_list.h)