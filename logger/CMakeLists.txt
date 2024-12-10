project(logger)
cmake_minimum_required(VERSION 3.10)

set(CURRENT_TARGET logger)

set(headers
    logger/include/cout_commiter.hpp
    logger/include/file_commiter.hpp
    logger/include/log_asserter.hpp
    logger/include/log_displayer.hpp
    logger/include/log_init.hpp
    logger/include/log.hpp
    logger/include/mixin_commiter.hpp
    logger/include/null_commiter.hpp
    logger/include/severity_type.hpp
    logger/include/stream_commiter.hpp)

set(sources
    src/file_commiter.cpp
    src/thread_commiter.cpp)

build_lib_component(STATIC HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                ${sources} HEADERS ${headers})

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})

addTestingDirectory(tests)
