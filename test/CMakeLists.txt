include(${PROJECT_SOURCE_DIR}/targets.cmake)

set(TEST_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/component_test.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/entity_manager_test.cc
)

# Test target
set(TEST_EXECUTABLE game_test)
add_executable(${TEST_EXECUTABLE} "${TEST_SOURCE}")
set_target_properties(${TEST_EXECUTABLE} PROPERTIES LINKER_LANGUAGE CXX)

# Google Test
find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIR})
target_link_libraries(${TEST_EXECUTABLE} ${GTEST_LIBRARIES})
target_link_libraries(${TEST_EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_EXECUTABLE} ${GAME_LIB})
