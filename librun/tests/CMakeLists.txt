cmake_minimum_required (VERSION 3.14)
project(lib_test_mode CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    main
)

add_test_executable(SOURCE_TESTS ${SOURCE_TESTS})

target_link_libraries(${CURRENT_TARGET}
  PRIVATE mtypes)
