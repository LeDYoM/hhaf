cmake_minimum_required (VERSION 3.14)
project(fsu_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    file_system
)

add_test_executable_with_main(SOURCE_TESTS ${SOURCE_TESTS})
set_compile_warning_level_and_cxx_properties_for_tests(${CURRENT_TARGET})

target_sources(${CURRENT_TARGET} PRIVATE file_driver_test.hpp)
target_link_libraries(${CURRENT_TARGET} PRIVATE fsu)
