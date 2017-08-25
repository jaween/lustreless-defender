CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(game)
set(VERSION_MAJOR "0")
set(VERSION_MAJOR "1")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")

# Build options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -MMD -MP")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Game target
set(MAIN_EXECUTABLE diffraction)
add_subdirectory(main)
add_executable(${MAIN_EXECUTABLE} "${SOURCE}")
set_target_properties(${MAIN_EXECUTABLE} PROPERTIES LINKER_LANGUAGE CXX)

# Test target
set(TEST_EXECUTABLE diffraction_test)
add_subdirectory(test)
add_executable(${TEST_EXECUTABLE} "${TEST_SOURCE}")
set_target_properties(${TEST_EXECUTABLE} PROPERTIES LINKER_LANGUAGE CXX)

# TODO(jaween): Find a better location to put this line
include_directories(main/include)

# TODO(jaween): This isn't platform agnostic (will get rid of this lib anyway)
# SDL_gpu
include_directories(/usr/local/include/SDL2)
link_directories(/usr/local/lib)
target_link_libraries(${MAIN_EXECUTABLE} SDL2_gpu)

# SDL 2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${MAIN_EXECUTABLE} ${SDL2_LIBRARIES})

# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${OPENGL_INCUDE_DIR} ${GLEW_INCLUDE_DIRS})
target_link_libraries(${MAIN_EXECUTABLE} ${OPENGL_LIBRARIES})
target_link_libraries(${MAIN_EXECUTABLE} ${GLEW_LIBRARIES})

# Google Test
find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIR})
target_link_libraries(${TEST_EXECUTABLE} ${GTEST_LIBRARIES})
target_link_libraries(${TEST_EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})
