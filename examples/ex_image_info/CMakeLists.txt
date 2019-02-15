cmake_minimum_required(VERSION 3.13)

project(ex_image_info)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex_image_info.o ex_image_info.cpp)

target_link_libraries(ex_image_info.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND ex_image_info.o
    DEPENDS ex_image_info.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
