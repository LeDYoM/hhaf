# Properties->C/C++->General->Additional Include Directories
set (LIB_BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set (LIB_DIRECTORY "${LIB_BASE_DIRECTORY}lib/")

file (GLOB LIB_CORE_HEADERS "${LIB_DIRECTORY}core/*.hpp")
file (GLOB LIB_CORE_SOURCES "${LIB_DIRECTORY}core/*.cpp")

file (GLOB LIB_CORE_EVENTS_HEADERS "${LIB_DIRECTORY}core/events/*.hpp")
file (GLOB LIB_CORE_EVENTS_SOURCES "${LIB_DIRECTORY}core/events/*.cpp")

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

file (GLOB_RECURSE LIB_HEADERS "${LIB_DIRECTORY}*.hpp")
file (GLOB_RECURSE LIB_SOURCES "${LIB_DIRECTORY}*.cpp")

#Add SFML directories
link_directories ("${PROJECT_SOURCE_DIR}/SFML/lib")
include_directories ("${PROJECT_SOURCE_DIR}/SFML/include")
include_directories (${LIB_BASE_DIRECTORY})

file (GLOB ZOPER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file (GLOB ZOPER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


add_executable (host ${ZOPER_HEADERS} ${ZOPER_SOURCES} ${LIB_HEADERS} ${LIB_SOURCES})

# Define source groups for lib
#source_group("lib\\Header Files" FILES ${LIB_HEADERS})
#source_group("lib\\Source Files" FILES ${LIB_SOURCES})
source_group("lib\\include" FILES ${LIB_INCLUDE_HEADERS})
source_group("lib\\core" FILES ${LIB_CORE_HEADERS} ${LIB_CORE_SOURCES})
source_group("lib\\core\\events" FILES ${LIB_CORE_EVENTS_HEADERS} ${LIB_CORE_EVENTS_SOURCES})
source_group("lib\\draw" FILES ${LIB_DRAW_HEADERS} ${LIB_DRAW_SOURCES})
source_group("lib\\menu" FILES ${LIB_MENU_HEADERS} ${LIB_MENU_SOURCES})
source_group("lib\\board" FILES ${LIB_BOARD_HEADERS} ${LIB_SOURCES})


# Define SFML libraries depending on Configuration
target_link_libraries(host 
	debug sfml-system-d
	debug sfml-window-d
	debug sfml-graphics-d
	debug sfml-main-d
	
	optimized sfml-system
	optimized sfml-window
	optimized sfml-graphics
	optimized sfml-main
	)

set (SFML_LINK_DLLS_DIR ${PROJECT_SOURCE_DIR}/SFML/shared/)
#message("SFML_LINK_DLLS_DIR:" ${SFML_LINK_DLLS_DIR})

add_custom_target(copy_sfml)
add_custom_command(TARGET copy_sfml PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${SFML_LINK_DLLS_DIR}$<CONFIG>
	$<TARGET_FILE_DIR:host>)

add_custom_target(copy_zoper_data)
add_custom_command(TARGET copy_zoper_data PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/zoper/data/
	$<TARGET_FILE_DIR:host>)


# Copy SFML dlls to Target directory
#add_custom_command(TARGET host POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${SFML_LINK_DLLS_DIR}$<CONFIG>
#        $<TARGET_FILE_DIR:host>)


# Install part
# Copy SFML to bin
#add_custom_command(TARGET INSTALL POST_BUILD        # Adds a post-build event to MyTest
#    COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_if_different..."
#        "${PROJECT_SOURCE_DIR}/SFML/shared"      # <--this is in-file
#        "${PROJECT_BINARY_DIR}/bin")                 # <--this is out-file path
		
# Adds logic to INSTALL.vcproj to copy host.exe to destination directory
install (TARGETS host RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
#install(FILES ${SFML_LINK_DLLS_DIR}$<CONFIG>/*.dll DESTINATION ${PROJECT_BINARY_DIR}/bin)
# Copy all assets to resources file
#INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${INSTALL_PATH}/assets FILES_MATCHING PATTERN "*.dae"  PATTERN "*.jpg")
