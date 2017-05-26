
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

file (GLOB LIB_SCENE_SCENE_HEADERS "${SCENE_NAMESPACEBASE_DIRECTORY}/nodes/*.hpp")
file (GLOB LIB_SCENE_SCENE_SOURCES "${SCENE_NAMESPACEBASE_DIRECTORY}/nodes/*.cpp")

file (GLOB LIB_SCENE_COMPONENTS_HEADERS "${SCENE_NAMESPACEBASE_DIRECTORY}/components/*.hpp")
file (GLOB LIB_SCENE_COMPONENTS_SOURCES "${SCENE_NAMESPACEBASE_DIRECTORY}/components/*.cpp")

file (GLOB LIB_INCLUDE_HEADERS "include/*.hpp")

file (GLOB LIB_GUI_HEADERS "gui/*.hpp")
file (GLOB LIB_GUI_SOURCES "gui/*.cpp")

file (GLOB LIB_UTT_HEADERS "utt/*.hpp")
file (GLOB LIB_UTT_SOURCES "utt/*.cpp")

#TO DO: A separated lib?
file (GLOB LIB_BOARD_HEADERS "board/*.hpp")
file (GLOB LIB_BOARD_SOURCES "board/*.cpp")

#Add all the file from the library to compile
file (GLOB_RECURSE LIB_HEADERS "*.hpp")
file (GLOB_RECURSE LIB_SOURCES "*.cpp")

include_directories ("..")

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

# Define source groups for lib
source_group("lib\\include" FILES ${LIB_INCLUDE_HEADERS})
source_group("lib\\backend" FILES ${LIB_BACKEND_HEADERS} ${LIB_BACKEND_SOURCES})
source_group("lib\\backend\\sfml" FILES ${LIB_BACKEND_SFML_IMPL_HEADERS} ${LIB_BACKEND_SFML_IMPL_SOURCES})
source_group("lib\\core" FILES ${LIB_CORE_HEADERS} ${LIB_CORE_SOURCES})
source_group("lib\\core\\events" FILES ${LIB_CORE_EVENTS_HEADERS} ${LIB_CORE_EVENTS_SOURCES})
source_group("lib\\scene" FILES ${LIB_SCENE_HEADERS} ${LIB_SCENE_SOURCES})
source_group("lib\\scene\\nodes" FILES ${LIB_SCENE_NODES_HEADERS} ${LIB_SCENE_NODES_SOURCES})
source_group("lib\\scene\\components" FILES ${LIB_SCENE_COMPONENTS_HEADERS} ${LIB_SCENE_COMPONENTS_SOURCES})
source_group("lib\\gui" FILES ${LIB_GUI_HEADERS} ${LIB_GUI_SOURCES})
source_group("lib\\board" FILES ${LIB_BOARD_HEADERS} ${LIB_BOARD_SOURCES})
source_group("lib\\utt" FILES ${LIB_UTT_HEADERS} ${LIB_UTT_SOURCES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set (SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")
#set(SFML_STATIC_LIBRARIES TRUE)
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${CURRENT_TARGET} ${SFML_LIBRARIES})
endif()


set(_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

#set_target_properties(${CURRENT_TARGET}
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${_OUTPUT_DIRECTORY}"
#)

#install (TARGETS ${CURRENT_TARGET} ARCHIVE DESTINATION ${_OUTPUT_DIRECTORY})
