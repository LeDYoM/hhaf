cmake_minimum_required(VERSION 3.14)
project(glad LANGUAGES C)

set(CURRENT_TARGET glad)

set(sources
  src/glad.c
  include/glad/glad.h
  include/KHR/khrplatform.h
)

message("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA: ${sources}")
add_library(${CURRENT_TARGET} SHARED ${sources})
#set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
target_include_directories(${CURRENT_TARGET} PUBLIC include)
target_compile_definitions(${CURRENT_TARGET} PUBLIC GLAD_GLAPI_EXPORT)
target_compile_definitions(${CURRENT_TARGET} PRIVATE GLAD_GLAPI_EXPORT_BUILD)