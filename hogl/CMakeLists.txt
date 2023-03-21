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
  ${include_dir}/buffer_functions.hpp
  ${include_dir}/low_level_constants.hpp
  ${include_dir}/ogl_export.hpp
  ${include_dir}/render_system_functions.hpp
  ${include_dir}/render_target.hpp
  ${include_dir}/shader_functions.hpp
  ${include_dir}/types.hpp
  ${include_dir}/uniform_functions.hpp
  ${include_dir}/vao_functions.hpp
  )

set(sources
  src/buffer_functions.cpp
  src/low_level_constants.cpp
  src/render_system_functions.cpp
  src/render_target.cpp
  src/shader_functions.cpp
  src/types_private.hpp
  src/types.cpp
  src/uniform_functions.cpp
  src/vao_functions.cpp
  )

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

#target_compile_definitions(${CURRENT_TARGET} PRIVATE backend_client_EXPORTS)
target_compile_definitions(${CURRENT_TARGET} PRIVATE hogl_EXPORTS)
target_link_libraries(${CURRENT_TARGET} PRIVATE log_and_types)
target_link_libraries(${CURRENT_TARGET} PUBLIC glad)

set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})
