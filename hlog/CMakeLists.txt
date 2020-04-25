cmake_minimum_required(VERSION 3.11)
project(hlog)

set(CURRENT_TARGET hlog)

set(SOURCES "src/hlog.cpp")

build_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${SOURCES}
)

target_compile_definitions(${CURRENT_TARGET} PRIVATE HLOG_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PUBLIC logger)
target_link_libraries(${CURRENT_TARGET} PUBLIC mtypes)
