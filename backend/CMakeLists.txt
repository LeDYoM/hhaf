cmake_minimum_required(VERSION 3.14)
project(backend
    VERSION 0.0.2.0
    DESCRIPTION "Backend module for haf"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET ${PROJECT_NAME})

set(sources
    src/backend_creator.cppm
    src/backend_factory.cppm
    src/backend_log.cppm
    src/backend_register.cppm
    src/backend_utils.cppm
    src/backend.cppm
)

build_lib_module(${CURRENT_TARGET} STATIC SOURCES "${sources}")

target_link_libraries(${CURRENT_TARGET} PRIVATE agloader log_and_types facil_math hlog)
target_link_libraries(${CURRENT_TARGET} PUBLIC backend_dev)
