cmake_minimum_required (VERSION 3.14)
project(mtypes_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    array
    lockablevector
    main
    menum
    object
    object_utils
    parpar
    str
    vector
)

add_test_executable(SOURCE_TESTS ${SOURCE_TESTS})

target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
