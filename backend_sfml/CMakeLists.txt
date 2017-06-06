project (bsfml)

file (GLOB _SOURCES "*.cpp")
file (GLOB _HEADERS "*.hpp")
 
#file (GLOB _INCLUDES "include/*.hpp")

set (CURRENT_TARGET bsfml) 
source_group("Sources" FILES ${_SOURCES})
source_group("Headers" FILES ${_HEADERS})
#source_group("Includes" FILES ${_INCLUDES})
#set(CMAKE_DEBUG_POSTFIX  "d") 

add_library(${CURRENT_TARGET} 
	SHARED
	${_SOURCES} 
	${_HEADERS}
#	${_INCLUDES}
)

#Patch for testing
#TO DO: Remove it (use a variable)
include_directories ("../lib/backend")
include_directories ("..")
target_link_libraries(${CURRENT_TARGET} lib)

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

#install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION .)

#set(LOADER_INCLUDE "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
#message("loader include directory: " ${LOADER_INCLUDE})