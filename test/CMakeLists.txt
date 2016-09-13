project(InterProcessAPI)
cmake_minimum_required(VERSION 3.0)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  )

link_directories(
  ${CMAKE_BINARY_DIR}
  )

add_definitions("-std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(sources
  ${CMAKE_SOURCE_DIR}/test/ChildDestructionTest.cpp
  ${CMAKE_SOURCE_DIR}/test/ChildConfirmationTest.cpp
  ${CMAKE_SOURCE_DIR}/test/InvalidProcessHandlingTest.cpp
  ${CMAKE_SOURCE_DIR}/test/TestsMain.cpp
  )

add_executable(ProcessTest ${sources})
target_link_libraries(ProcessTest Interprocess)
target_link_libraries(ProcessTest gtest)
