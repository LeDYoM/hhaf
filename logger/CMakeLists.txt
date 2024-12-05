project(logger)
cmake_minimum_required(VERSION 3.9.2)

set(CURRENT_TARGET logger)

add_library(${CURRENT_TARGET} INTERFACE)
target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})
target_sources(${CURRENT_TARGET} PRIVATE
    logger/include/log_asserter.hpp
    logger/include/log_displayer.hpp
    logger/include/log_init.hpp
    logger/include/log.hpp
    logger/include/mixin_commiter.hpp
    logger/include/null_commiter.hpp
    logger/include/severity_type.hpp
    logger/include/stream_commiter.hpp)