
# The version number.
set (LIB_VERSION_MAJOR 1)
set (LIB_VERSION_MINOR 2)
set (LIB_VERSION_PATCH 3)

set (LIB_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories(${PROJECT_BINARY_DIR})
  
file (GLOB LIB_CORE_HEADERS "core/*.hpp")
file (GLOB LIB_CORE_SOURCES "core/*.cpp")

file (GLOB LIB_CORE_EVENTS_HEADERS "core/events/*.hpp")
file (GLOB LIB_CORE_EVENTS_SOURCES "core/events/*.cpp")

file (GLOB LIB_BACKEND_HEADERS "backend/*.hpp")
file (GLOB LIB_BACKEND_SOURCES "backend/*.cpp")
file (GLOB LIB_BACKEND_SFML_IMPL_HEADERS "backend/sfml/*.hpp")
file (GLOB LIB_BACKEND_SFML_IMPL_SOURCES "backend/sfml/*.cpp")

set (SCENE_NAMESPACEBASE_DIRECTORY "scene")
file (GLOB LIB_SCENE_HEADERS "${SCENE_NAMESPACEBASE_DIRECTORY}/*.hpp")
file (GLOB LIB_SCENE_SOURCES "${SCENE_NAMESPACEBASE_DIRECTORY}/*.cpp")

file (GLOB LIB_SCENE_NODES_HEADERS "${SCENE_NAMESPACEBASE_DIRECTORY}/nodes/*.hpp")
file (GLOB LIB_SCENE_NODES_SOURCES "${SCENE_NAMESPACEBASE_DIRECTORY}/nodes/*.cpp")

file (GLOB LIB_SCENE_COMPONENTS_HEADERS "${SCENE_NAMESPACEBASE_DIRECTORY}/components/*.hpp")
file (GLOB LIB_SCENE_COMPONENTS_SOURCES "${SCENE_NAMESPACEBASE_DIRECTORY}/components/*.cpp")

file (GLOB LIB_GUI_HEADERS "gui/*.hpp")
file (GLOB LIB_GUI_SOURCES "gui/*.cpp")

#TO DO: A separated lib?
file (GLOB LIB_BOARD_HEADERS "board/*.hpp")
file (GLOB LIB_BOARD_SOURCES "board/*.cpp")

set (INCLUDE_DIRECTORY "include")
file (GLOB LIB_INCLUDE_HEADERS "${INCLUDE_DIRECTORY}/*.hpp")

file (GLOB LIB_CONTAINERS_HEADERS "${INCLUDE_DIRECTORY}/containers/*.hpp")
#file (GLOB LIB_CONTAINERS_SOURCES "${INCLUDE_DIRECTORY}/containers/*.cpp")

file (GLOB LIB_TYPES_HEADERS "${INCLUDE_DIRECTORY}/types/*.hpp")
file (GLOB LIB_TYPES_SOURCES "types/*.cpp")

#Add all the file from the library to compile
file (GLOB_RECURSE LIB_HEADERS "*.hpp")
file (GLOB_RECURSE LIB_SOURCES "*.cpp")

include_directories ("..")

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

# Define source groups for lib
source_group("lib\\include" FILES ${LIB_INCLUDE_HEADERS})
source_group("lib\\containers" FILES ${LIB_CONTAINERS_HEADERS} ${LIB_CONTAINERS_SOURCES})
source_group("lib\\types" FILES ${LIB_TYPES_HEADERS} ${LIB_TYPES_SOURCES})
source_group("lib\\backend" FILES ${LIB_BACKEND_HEADERS} ${LIB_BACKEND_SOURCES})
source_group("lib\\backend\\sfml" FILES ${LIB_BACKEND_SFML_IMPL_HEADERS} ${LIB_BACKEND_SFML_IMPL_SOURCES})
source_group("lib\\core" FILES ${LIB_CORE_HEADERS} ${LIB_CORE_SOURCES})
source_group("lib\\core\\events" FILES ${LIB_CORE_EVENTS_HEADERS} ${LIB_CORE_EVENTS_SOURCES})
source_group("lib\\scene" FILES ${LIB_SCENE_HEADERS} ${LIB_SCENE_SOURCES})
source_group("lib\\scene\\nodes" FILES ${LIB_SCENE_NODES_HEADERS} ${LIB_SCENE_NODES_SOURCES})
source_group("lib\\scene\\components" FILES ${LIB_SCENE_COMPONENTS_HEADERS} ${LIB_SCENE_COMPONENTS_SOURCES})
source_group("lib\\gui" FILES ${LIB_GUI_HEADERS} ${LIB_GUI_SOURCES})
source_group("lib\\board" FILES ${LIB_BOARD_HEADERS} ${LIB_BOARD_SOURCES})

include_directories(${CURRENT_TARGET} ${LOADER_INCLUDE})
target_link_libraries(${CURRENT_TARGET} loader)


set(_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

#set_target_properties(${CURRENT_TARGET}
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${_OUTPUT_DIRECTORY}"
#)

#install (TARGETS ${CURRENT_TARGET} ARCHIVE DESTINATION ${_OUTPUT_DIRECTORY})
