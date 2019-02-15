cmake_minimum_required(VERSION 3.13)

project(ex_imread)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex_imread.o ex_imread.cpp)

target_link_libraries(ex_imread.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND ex_imread.o
    DEPENDS ex_imread.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
