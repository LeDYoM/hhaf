project (bsfml)

file (GLOB _SOURCES "*.cpp")
file (GLOB _HEADERS "*.hpp")
 
set (CURRENT_TARGET bsfml) 

add_library(${CURRENT_TARGET} 
	SHARED
	${_SOURCES} 
	${_HEADERS}
)

#Patch for testing
#TO DO: Remove it (use a variable)
include_directories ("..")

target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)

# Detect and add SFML

#Set fallback directory for SFML
set (SFML_ROOT "${L3RD_PARTY_DIR}/SFML")

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${CURRENT_TARGET} PRIVATE ${SFML_LIBRARIES})
endif()

add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${SFML_ROOT}/bin
	$<TARGET_FILE_DIR:${CURRENT_TARGET}>)

install (TARGETS ${CURRENT_TARGET} 
	LIBRARY DESTINATION .
	RUNTIME DESTINATION .
)
