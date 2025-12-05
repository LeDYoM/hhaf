project("HAF MemManager"
    VERSION 0.2.0.0
    DESCRIPTION "Memory manager for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET memmanager)

if(MSVC)
  set(driver_file _msvc)
else()
  set(driver_file _null)
endif()

set(sources
    src/platforms/msvc/memmanager${driver_file}.cppm
    src/bytes.cppm
    src/configuration.cppm
    src/deletes.cppm
    src/memmanager_funcs.cppm
    src/memmanager.cppm
    src/memory_statistics.cppm
    src/memory_view.cppm
    src/news.cppm
)

build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}")

addTestingDirectory(tests)
