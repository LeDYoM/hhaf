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

set (CURRENT_TARGET host)

add_executable (${CURRENT_TARGET} ${ZOPER_HEADERS} ${ZOPER_SOURCES} ${LIB_HEADERS} ${LIB_SOURCES})

# Define source groups for lib
#source_group("lib\\Header Files" FILES ${LIB_HEADERS})
#source_group("lib\\Source Files" FILES ${LIB_SOURCES})
source_group("lib\\include" FILES ${LIB_INCLUDE_HEADERS})
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


add_custom_target(copy_sfml)
add_custom_command(TARGET copy_sfml PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${SFML_ROOT}/bin
	$<TARGET_FILE_DIR:${CURRENT_TARGET}>)

add_custom_target(copy_zoper_data)
add_custom_command(TARGET copy_zoper_data PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/zoper/data/
	$<TARGET_FILE_DIR:${CURRENT_TARGET}>)


set(_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set_target_properties(${CURRENT_TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${_OUTPUT_DIRECTORY}"
)

if (MSVC)
	file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/${CURRENT_TARGET}.vcxproj.user" 
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>     \
    <Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    </Project>")
endif()

install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION ${_OUTPUT_DIRECTORY})
