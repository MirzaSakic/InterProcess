project(InterProcessAPI)
cmake_minimum_required(VERSION 3.0)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  )

add_definitions("-std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(sources
  ${CMAKE_SOURCE_DIR}/src/test.cpp
  )

add_executable(InterProcess ${sources})
target_link_libraries(InterProcess boost_system)
target_link_libraries(InterProcess pthread)
