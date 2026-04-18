cmake_minimum_required(VERSION 4.3)

project(0001)

add_executable(0001)

target_sources(0001
  PRIVATE
    src/main.cpp
)

add_subdirectory(lib)

target_link_libraries(0001
  PRIVATE
    lib
)
