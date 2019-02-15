cmake_minimum_required(VERSION 3.13)

project(helloworld)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(helloworld.o helloworld.cpp)
target_link_libraries(helloworld.o ${OpenCV_LIBS})
