include(${PROJECT_SOURCE_DIR}/targets.cmake)

set(LIBRARY_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/camera.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/highlight_shader.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/image.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/shadow_map_shader.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/light.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/shadow_mask_shader.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/solid_shader.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/engine.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/occlusion_mask_shader.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/texture_shader.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/entity.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/entity_manager.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/base_component.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/kinetic_component.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/transform_component.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/room.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/vector.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/shader.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/wave.cc
)

# Game library
add_library(${GAME_LIB} "${LIBRARY_SOURCE}")
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# TODO(jaween): This isn't platform agnostic (will get rid of this lib anyway)
# SDL_gpu
include_directories(/usr/local/include/SDL2)
link_directories(/usr/local/lib)
target_link_libraries(${GAME_LIB} SDL2_gpu)

# SDL 2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${GAME_LIB} ${SDL2_LIBRARIES})

# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${OPENGL_INCUDE_DIR} ${GLEW_INCLUDE_DIRS})
target_link_libraries(${GAME_LIB} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

# Game target
set(MAIN_EXECUTABLE diffraction)
set(MAIN_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
add_executable(${MAIN_EXECUTABLE} "${MAIN_SOURCE}")
set_target_properties(${MAIN_EXECUTABLE} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${MAIN_EXECUTABLE} ${GAME_LIB})

