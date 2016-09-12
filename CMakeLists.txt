project(InterProcessAPI)
cmake_minimum_required(VERSION 3.0)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  )

link_directories(
  ${CMAKE_BINARY_DIR}/
  )

add_definitions("-std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(sources
  ${CMAKE_SOURCE_DIR}/src/Process.cpp
  )

set(execsources
  ${CMAKE_SOURCE_DIR}/src/test.cpp
  )

add_library(Interprocess STATIC ${sources})
target_link_libraries(Interprocess boost_system)
target_link_libraries(Interprocess pthread)

add_executable(ipTest ${execsources})
target_link_libraries(ipTest Interprocess)


