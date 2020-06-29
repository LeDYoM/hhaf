cmake_minimum_required(VERSION 3.11)
project(hlog)

set(CURRENT_TARGET hlog)

set(SOURCES 
    src/cout_commiter.cpp
    src/file_commiter.cpp
    src/thread_commiter.cpp
    src/hlog.cpp)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SOURCES})

target_link_libraries(${CURRENT_TARGET} PUBLIC logger)
target_link_libraries(${CURRENT_TARGET} PUBLIC mtypes)
