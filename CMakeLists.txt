cmake_minimum_required(VERSION 3.17.2)
project (hello)

include_directories("include/")
LINK_DIRECTORIES("libs/")

add_executable(hello main.cpp src/glad.c)

target_link_libraries(hello libglfw3.a)