cmake_minimum_required(VERSION 3.14)
project(ISpyAFake)

set(CMAKE_CXX_STANDARD 14)

add_executable(ISpyAFake main.cpp Player.cpp Player.h Category.cpp Category.h CategoryItem.h CategoryAssignment.cpp CategoryAssignment.h)