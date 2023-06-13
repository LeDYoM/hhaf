cmake_minimum_required (VERSION 3.14)
project(facil_math_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    rect
    vector2d
    vector3d
    vector4d
)

add_test_executable_with_main(SOURCE_TESTS ${SOURCE_TESTS})
set_compile_warning_level_and_cxx_properties_for_tests(${CURRENT_TARGET})

target_link_libraries(${CURRENT_TARGET} PRIVATE htypes)
