cmake_minimum_required (VERSION 3.14)
project(facil_math_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    matrix4x4
    rect
    vector2d
    vector3d
    vector4d
    vvector
)

add_test_executable_with_main(SOURCE_TESTS ${SOURCE_TESTS})
set_compile_warning_level_and_cxx_properties_for_tests(${CURRENT_TARGET})

target_link_libraries(${CURRENT_TARGET} PRIVATE htypes)

#set(do_benchmark 1)

if (DEFINED do_benchmark)
    set(BENCHMARK_SOURCES
        matrix4x4.benchmark
    )

    set(CURRENT_TARGET "${CURRENT_TARGET}_benchmark")
    add_haf_test_executable(SOURCE_TESTS ${BENCHMARK_SOURCES})
    set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})
endif()
