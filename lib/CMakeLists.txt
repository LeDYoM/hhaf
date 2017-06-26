project (lib)

# The version number.
set (LIB_VERSION_MAJOR 1)
set (LIB_VERSION_MINOR 3)
set (LIB_VERSION_PATCH 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories(${PROJECT_BINARY_DIR})
  
#Add all the file from the library to compile
file (GLOB_RECURSE LIB_HEADERS "*.hpp")
file (GLOB_RECURSE LIB_SOURCES "*.cpp")

include_directories ("..")

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LIB_HEADERS} ${LIB_SOURCES})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
