project (loader)

file (GLOB _SOURCES "*.cpp")
file (GLOB _HEADERS "*.hpp")
 
file (GLOB _INCLUDES "include/*.hpp")

set (CURRENT_TARGET loader) 
source_group("Sources" FILES ${_SOURCES})
source_group("Headers" FILES ${_HEADERS})
source_group("Includes" FILES ${_INCLUDES})
set(CMAKE_DEBUG_POSTFIX  "d") 

add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS} ${_INCLUDES})

install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION .)

set(LOADER_INCLUDE "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
message("loader include directory: " ${LOADER_INCLUDE})