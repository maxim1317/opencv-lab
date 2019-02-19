cmake_minimum_required(VERSION 3.13)

project(hist)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hist.o hist.cpp)

target_link_libraries(hist.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND hist.o
    DEPENDS hist.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
