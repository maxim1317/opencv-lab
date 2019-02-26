cmake_minimum_required(VERSION 3.13)

project(hist)

find_package(OpenCV REQUIRED)

message(" OpenCV version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

file(MAKE_DIRECTORY steps)
file(MAKE_DIRECTORY plot)

add_executable(hist src/hist.cpp src/headers/misc.cpp)

target_link_libraries(hist ${OpenCV_LIBS})

add_custom_target(run
    COMMAND hist
    DEPENDS hist
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
