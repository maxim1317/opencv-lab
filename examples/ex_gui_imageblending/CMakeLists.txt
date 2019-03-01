cmake_minimum_required(VERSION 3.13)

project(ex_gui_imageblending)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex_gui_imageblending ex_gui_imageblending.cpp)

target_link_libraries(ex_gui_imageblending ${OpenCV_LIBS})

add_custom_target(run
    COMMAND ex_gui_imageblending
    DEPENDS ex_gui_imageblending
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
