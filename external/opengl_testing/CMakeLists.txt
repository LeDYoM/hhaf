cmake_minimum_required(VERSION 3.14)
project(ogl_testing LANGUAGES CXX)

set(CURRENT_TARGET ogl_testing)

set(sources
  src/main.cpp
)

add_executable(${CURRENT_TARGET} ${sources})

target_link_libraries(${CURRENT_TARGET} PRIVATE
    glad
    sfml-system
    sfml-window
    sfml-graphics)
