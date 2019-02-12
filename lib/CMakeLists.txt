project (lib)

include_directories ("..")

set(LIB_VERSION_MAJOR "1")
set(LIB_VERSION_MINOR "6")
set(LIB_VERSION_PATCH "2")

file (GLOB_RECURSE _SOURCES "board/*.cpp" "core/*.cpp" "scene/*.cpp" "system/*.cpp")
file (GLOB_RECURSE _HEADERS "board/*.hpp" "core/*.hpp" "include/*.hpp" "scene/*.hpp" "system/*.cpp")

configure_file(config.hpp.in config.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} STATIC ${_SOURCES} ${_HEADERS})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)

add_subdirectory(tests)
