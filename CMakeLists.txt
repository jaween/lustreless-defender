CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(game)
set(VERSION_MAJOR "0")
set(VERSION_MAJOR "1")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")

# Build options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -MMD -MP")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# TODO(jaween): Find a better location to put this line
include_directories(main/include)

add_subdirectory(main)
add_subdirectory(test)
