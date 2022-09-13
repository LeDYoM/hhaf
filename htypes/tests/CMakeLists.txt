cmake_minimum_required (VERSION 3.14)
project(htypes_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    array
    connection
    dictionary
    function
    lockablevector
    main
    menum
    object
    object_utils
    parpar
    properties
    propertystate
    rect
    span
    str_literal
    str
    vector_view
    vector
    vector2d
    vector3d
)

add_test_executable(SOURCE_TESTS ${SOURCE_TESTS})
set_compile_warning_level_and_cxx_properties_for_tests(${CURRENT_TARGET})

target_link_libraries(${CURRENT_TARGET} PRIVATE htypes)
