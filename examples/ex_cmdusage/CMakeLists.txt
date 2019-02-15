cmake_minimum_required(VERSION 3.13)

project(ex_cmdusage)

find_package(OpenCV REQUIRED)

message("opencv version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex_cmdusage.o ex_cmdusage.cpp)

target_link_libraries(ex_cmdusage.o ${OpenCV_LIBS})

add_custom_target(run
    COMMAND ex_cmdusage.o
    DEPENDS ex_cmdusage.o
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
