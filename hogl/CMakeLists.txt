cmake_minimum_required(VERSION 3.14)
project(
  renderer
  VERSION 1.0.1.2
  DESCRIPTION "Library for rendering"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set (CURRENT_TARGET ${PROJECT_NAME})

set(include_dir hogl/include)
set(headers
  ${include_dir}/blend_mode.hpp
  ${include_dir}/render_element.hpp
  ${include_dir}/render_target.hpp
  ${include_dir}/renderer.hpp
  ${include_dir}/vertex_buffer.hpp
  )

set(sources
    opengl/gl_check.cpp
    opengl/gl_check.hpp
    opengl/glad.cpp
    opengl/glad.h
    opengl/khrplatform.h
    src/blend_mode.cpp
    src/render_element.cpp
    src/render_target.cpp
    src/renderer.cpp
    src/vertex_buffer.cpp
    )

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

#target_compile_definitions(${CURRENT_TARGET} PRIVATE backend_client_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PRIVATE
  backend_dev
  htypes)

set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})
