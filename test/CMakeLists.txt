cmake_minimum_required(VERSION 3.10)

# set the project name
project(Test)

link_libraries(RGE)

# add the executable
add_executable(Test main.cpp)