cmake_minimum_required(VERSION 3.11)
project(hlog LANGUAGES CXX)

set(CURRENT_TARGET hlog)

set(sources
    src/hlog.cppm
    )


build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}")

find_package(Threads REQUIRED)

target_link_libraries(${CURRENT_TARGET}
    PRIVATE Threads::Threads
    PUBLIC logger htypes)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
