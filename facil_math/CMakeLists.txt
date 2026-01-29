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
set(sources
    src/facil_math.cppm
    src/geometry_math.cppm
    src/math_types.cppm
    src/matrix4x4_functions.cppm
    src/matrix4x4.cppm
    src/rect.cppm
    src/vector_types.cppm
    src/vector2d.cppm
    src/vector3d.cppm
    src/vector4d.cppm
    src/vvector_functions.cppm
    src/vvector.cppm
)

build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}")
target_link_libraries(${CURRENT_TARGET} PRIVATE htypes)

addTestingDirectory(tests)
