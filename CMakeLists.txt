CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(game)
set(VERSION_MAJOR "0")
set(VERSION_MAJOR "1")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")

set(MAIN_EXECUTABLE diffraction)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -MMD -MP")

add_subdirectory(main)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
message("output dir is ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Game target
#add_executable(${EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/${SOURCES})
add_executable(${MAIN_EXECUTABLE} "${SOURCE}")
set_target_properties(${MAIN_EXECUTABLE} PROPERTIES LINKER_LANGUAGE CXX)

# TODO(jaween): Find a better location to put this line
include_directories(main/include)

# TODO(jaween): This isn't platform agnostic
# SDL_gpu Library
include_directories(/usr/local/include/SDL2)
link_directories(/usr/local/lib)
target_link_libraries(${MAIN_EXECUTABLE} SDL2_gpu)


#message("Source is ${SOURCE}")

link_directories(${PROJECT_SOURCE_DIR}/lib)

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
