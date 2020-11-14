cmake_minimum_required(VERSION 3.17.2)
project (maze3d)

file(GLOB_RECURSE TARGET_SRC
    "src/*.cpp"
    "src/*.hpp"
    "src/*.h"
    "src/*.c"
)

include_directories("include/" "src/" "src/engine/" "src/game")
LINK_DIRECTORIES("libs/")

SET(TARGET_SRC 
${TARGET_SRC}
"include/stb/stb_image.c"
"main.cpp"
)

add_executable(maze3d ${TARGET_SRC})

target_link_libraries(maze3d opengl32 libglfw3.a libassimp.dll.a libfreetype.a)
set_target_properties(maze3d PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Maze3d )