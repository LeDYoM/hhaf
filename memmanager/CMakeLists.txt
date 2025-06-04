project("HAF MemManager"
    VERSION 0.2.0.0
    DESCRIPTION "Memory manager for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET memmanager)

set(sources
    src/platforms/msvc/memmanager_msvc.cpp
    src/memmanager_platform.hpp
    src/memmanager.cpp
    src/memory_statistics_private.hpp
    src/memory_statistics.cpp
)

set(headers
    memmanager/include/memmanager.hpp
    memmanager/include/memory_statistics.hpp
    memmanager/include/memory_view.hpp
)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    "${sources}" HEADERS "${headers}" )

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
target_link_libraries(${CURRENT_TARGET} PRIVATE parpar)
target_include_directories(${CURRENT_TARGET} PRIVATE src)