cmake_minimum_required(VERSION 3.5)
project(Tagger)

set(CMAKE_CXX_STANDARD 11)

add_executable(Tagger main2_For_Tests.cpp AVL_Tree.h List.h ImageTagger.h Image.h ImageTagger.cpp Image.cpp library2.h exceptions.h library2.cpp)