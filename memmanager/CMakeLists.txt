project("HAF MemManager"
    VERSION 0.2.0.0
    DESCRIPTION "Memory manager for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET memmanager)

set(sources
    src/platforms/msvc/memmanager_msvc.cppm
    src/configuration.cppm
    src/memmanager_funcs.cppm
    src/memmanager.cppm
    src/memory_statistics.cppm
    src/memory_view.cppm
)

build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}")
#target_link_libraries(${CURRENT_TARGET} PRIVATE parpar)
