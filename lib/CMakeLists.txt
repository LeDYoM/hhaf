
# The version number.
set (LIB_VERSION_MAJOR 1)
set (LIB_VERSION_MINOR 2)
set (LIB_VERSION_PATCH 1)

set (LIB_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${LIB_DIRECTORY}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories(${PROJECT_BINARY_DIR})
  
file (GLOB LIB_CORE_HEADERS "${LIB_DIRECTORY}core/*.hpp")
file (GLOB LIB_CORE_SOURCES "${LIB_DIRECTORY}core/*.cpp")

file (GLOB LIB_CORE_EVENTS_HEADERS "${LIB_DIRECTORY}core/events/*.hpp")
file (GLOB LIB_CORE_EVENTS_SOURCES "${LIB_DIRECTORY}core/events/*.cpp")

file (GLOB LIB_BACKEND_HEADERS "${LIB_DIRECTORY}backend/*.hpp")
file (GLOB LIB_BACKEND_SOURCES "${LIB_DIRECTORY}backend/*.cpp")

file (GLOB LIB_DRAW_HEADERS "${LIB_DIRECTORY}draw/*.hpp")
file (GLOB LIB_DRAW_SOURCES "${LIB_DIRECTORY}draw/*.cpp")

file (GLOB LIB_INCLUDE_HEADERS "${LIB_DIRECTORY}include/*.hpp")
#file (GLOB LIB_BASE_SOURCES "${LIB_DIRECTORY}include/*.cpp")

#TO DO: A separated lib?
file (GLOB LIB_MENU_HEADERS "${LIB_DIRECTORY}menu/*.hpp")
file (GLOB LIB_MENU_SOURCES "${LIB_DIRECTORY}menu/*.cpp")

#TO DO: A separated lib?
file (GLOB LIB_BOARD_HEADERS "${LIB_DIRECTORY}board/*.hpp")
file (GLOB LIB_BOARD_SOURCES "${LIB_DIRECTORY}board/*.cpp")

#Add all the file from the library to compile
file (GLOB_RECURSE LIB_HEADERS "${LIB_DIRECTORY}*.hpp")
file (GLOB_RECURSE LIB_SOURCES "${LIB_DIRECTORY}*.cpp")

include_directories ("${LIB_DIRECTORY}..")

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

# Define source groups for lib
#source_group("lib\\Header Files" FILES ${LIB_HEADERS})
#source_group("lib\\Source Files" FILES ${LIB_SOURCES})
source_group("lib\\include" FILES ${LIB_INCLUDE_HEADERS})
source_group("lib\\backend" FILES ${LIB_BACKEND_HEADERS} ${LIB_BACKEND_SOURCES})
source_group("lib\\core" FILES ${LIB_CORE_HEADERS} ${LIB_CORE_SOURCES})
source_group("lib\\core\\events" FILES ${LIB_CORE_EVENTS_HEADERS} ${LIB_CORE_EVENTS_SOURCES})
source_group("lib\\draw" FILES ${LIB_DRAW_HEADERS} ${LIB_DRAW_SOURCES})
source_group("lib\\menu" FILES ${LIB_MENU_HEADERS} ${LIB_MENU_SOURCES})
source_group("lib\\board" FILES ${LIB_BOARD_HEADERS} ${LIB_SOURCES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set (SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${CURRENT_TARGET} ${SFML_LIBRARIES})
endif()


set(_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

#set_target_properties(${CURRENT_TARGET}
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${_OUTPUT_DIRECTORY}"
#)

install (TARGETS ${CURRENT_TARGET} ARCHIVE DESTINATION ${_OUTPUT_DIRECTORY})
