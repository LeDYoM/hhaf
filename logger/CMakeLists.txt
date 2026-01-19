cmake_minimum_required(VERSION 3.14)
project(logger
    VERSION 1.2.0.0
    LANGUAGES CXX)

set(CURRENT_TARGET logger)

set(sources
    src/commiters/cout_commiter.cppm
    src/commiters/file_commiter.cppm
    src/commiters/mixin_commiter.cppm
    src/commiters/null_commiter.cppm
    src/commiters/stream_commiter.cppm
#    src/commiters/thread_commiter_impl_sl.cppm
    src/commiters/thread_commiter_impl.cppm
#    src/commiters/thread_commiter_sl.cppm
    src/commiters/thread_commiter.cppm
    src/log_asserter.cppm
    src/log_displayer.cppm
    src/log_init.cppm
    src/log.cppm
    src/logger.cppm
    src/severity_type.cppm
)

build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}")

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
message(STATUS "Logger...")
message(STATUS "Version ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
addTestingDirectory(tests)
