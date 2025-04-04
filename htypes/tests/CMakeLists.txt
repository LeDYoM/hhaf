cmake_minimum_required (VERSION 3.14)
project(htypes_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    array
    dictionary
    function
    hash
    lockable_vector
    menum
    shared_ptr
    span
    stack
    str_functions
    str_literal
    str_view
    str
    unique_ptr
    vector
    weak_ptr
)

add_test_executable_with_main(SOURCE_TESTS ${SOURCE_TESTS})
set_compile_warning_level_and_cxx_properties_for_tests(${CURRENT_TARGET})

target_link_libraries(${CURRENT_TARGET} PRIVATE htypes)
