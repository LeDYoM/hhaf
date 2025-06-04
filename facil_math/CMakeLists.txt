set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("HAF Types"
    VERSION 0.0.1.0
    DESCRIPTION "Math Facilitator"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET facil_math)

set(include_dir facil_math/include)
set(headers
    ${include_dir}/geometry_math.hpp
    ${include_dir}/math_types.hpp
    ${include_dir}/matrix4x4_functions.hpp
    ${include_dir}/matrix4x4.hpp
    ${include_dir}/rect.hpp
    ${include_dir}/vector_types.hpp
    ${include_dir}/vector2d.hpp
    ${include_dir}/vector3d.hpp
    ${include_dir}/vector4d.hpp
    ${include_dir}/vvector_functions.hpp
    ${include_dir}/vvector.hpp
  )

build_lib_component(HEADERS_ONLY HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
              HEADERS ${headers})

set_pragma_once_or_not(FMA true INTERFACE)

target_compile_features(${CURRENT_TARGET} INTERFACE cxx_std_23)

addTestingDirectory(tests)
