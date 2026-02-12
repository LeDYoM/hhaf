cmake_minimum_required(VERSION 3.14)
project(
  renderer
  VERSION 1.0.1.2
  DESCRIPTION "Library for rendering"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set (CURRENT_TARGET ${PROJECT_NAME})

set(sources_nm
  src/opengl/gl_check.cpp
  src/opengl/gl_check.hpp
  src/opengl/glad.cpp
  src/opengl/glad.h
  src/opengl/khrplatform.h)

set(sources
  src/blend_mode.cppm
  src/render_element.cppm
  src/render_target.cppm
  src/renderer.cppm
  src/vertex_buffer.cppm)

build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}" SOURCES_NM "${sources_nm}")

#target_compile_definitions(${CURRENT_TARGET} PRIVATE backend_client_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PRIVATE
  backend_dev
  htypes
  facil_math)

set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})
