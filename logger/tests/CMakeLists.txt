cmake_minimum_required (VERSION 3.14)
project(logger_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    log
    log_asserter
    log_displayer
    log_severity
    log_thread
)

add_test_executable_with_main(SOURCE_TESTS ${SOURCE_TESTS})
target_sources(${CURRENT_TARGET} PRIVATE include/log_stream_test.hpp)
set_compile_warning_level_and_cxx_properties_for_tests(${CURRENT_TARGET})

target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
