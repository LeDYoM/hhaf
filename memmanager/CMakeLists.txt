project("HAF MemManager"
    VERSION 0.2.0.0
    DESCRIPTION "Memory manager for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET memmanager)

set(sources 
    src/memmanager.cpp
    src/memory_statistics.cpp
    src/memory_statistics.hpp
)

set(headers memmanager/include/memmanager.hpp)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    "${sources}" HEADERS "${headers}" )
 
