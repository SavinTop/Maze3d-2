cmake_minimum_required(VERSION 3.17.2)
project (maze3d)

file(GLOB helloworld_SRC
    "*.h"
    "*.cpp"
)

include_directories("include/" "src/")
LINK_DIRECTORIES("libs/")

SET(TARGET_SRC
    main.cpp
    src/glad.c
    src/render/shader.cpp
    src/utilities/fileLoader.cpp
    src/baseTypes/resource.cpp
    src/baseTypes/disk_file_text_res.cpp
    )

add_executable(maze3d ${TARGET_SRC})

target_link_libraries(maze3d libglfw3.a)