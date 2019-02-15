cmake_minimum_required(VERSION 3.13)

project(ex_mat_create_print)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex_mat_create_print.o ex_mat_create_print.cpp)

target_link_libraries(ex_mat_create_print.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND ex_mat_create_print.o
    DEPENDS ex_mat_create_print.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
