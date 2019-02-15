cmake_minimum_required(VERSION 3.13)

project(ex_drawing_circle)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex_drawing_circle.o ex_drawing_circle.cpp)

target_link_libraries(ex_drawing_circle.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND ex_drawing_circle.o
    DEPENDS ex_drawing_circle.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
