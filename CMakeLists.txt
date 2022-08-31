cmake_minimum_required(VERSION 3.1)
project(DocumentScanner)

# set(CMAKE_GXX_FLAGS "-Wall -Wextra -Wconversion  -pedantic -std=gnu11")


# external libraries
# find_library(OpenCV_LIBS NAMES opencv4 opencv PATHS $HOME/.local/lib)
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# src directory
file(GLOB_RECURSE SRC_FILES src/**.cpp)

# foreach(child ${SRC_FILES})
#     message("${child}") 
# endforeach()

# add executable
add_executable( main main.cpp ${SRC_FILES} )
target_link_libraries( main ${OpenCV_LIBS})

