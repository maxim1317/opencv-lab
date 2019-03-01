cmake_minimum_required(VERSION 3.13)

project(rects)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rects.o rects.cpp)

target_link_libraries(rects.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND rects.o
    DEPENDS rects.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
