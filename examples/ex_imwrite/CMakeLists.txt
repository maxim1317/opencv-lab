cmake_minimum_required(VERSION 3.13)

project(ex_imwrite)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex_imwrite.o ex_imwrite.cpp)

target_link_libraries(ex_imwrite.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND ex_imwrite.o
    DEPENDS ex_imwrite.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
