cmake_minimum_required(VERSION 3.17.2)
project (maze3d)

file(GLOB_RECURSE TARGET_SRC
    "src/*.cpp"
    "src/*.c"
)

include_directories("include/" "src/" "src/engine/")
LINK_DIRECTORIES("libs/")

SET(TARGET_SRC 
${TARGET_SRC}
"include/stb/stb_image.c"
"main.cpp"
)

add_executable(maze3d ${TARGET_SRC})

target_link_libraries(maze3d libglfw3.a libassimp.dll.a)