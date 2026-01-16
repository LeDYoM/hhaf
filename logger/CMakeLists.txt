cmake_minimum_required(VERSION 3.14)
project(logger
    VERSION 1.2.0.0
    LANGUAGES CXX)

set(CURRENT_TARGET logger)
#[[
set(headers
    logger/include/commiters/cout_commiter.hpp
    logger/include/commiters/file_commiter.hpp
    logger/include/commiters/mixin_commiter.hpp
    logger/include/commiters/null_commiter.hpp
    logger/include/commiters/stream_commiter.hpp
    logger/include/commiters/thread_commiter.hpp
    logger/include/log_asserter.hpp
    logger/include/log_displayer.hpp
    logger/include/log_init.hpp
    logger/include/log.hpp
    logger/include/severity_type.hpp
    )

set(sources
    src/commiters/file_commiter.cpp
    src/commiters/thread_commiter.cpp)
]]

set(sources
    src/commiters/file_commiter.cppm
    src/log_asserter.cppm
    src/log_displayer.cppm
    src/log_init.cppm
    src/log.cppm
    src/logger.cppm
    src/severity_type.cppm
)

build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}")

#build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
#                ${sources} HEADERS ${headers})

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
message(STATUS "Logger...")
message(STATUS "Version ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
addTestingDirectory(tests)
