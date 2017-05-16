#Add SFML directories

include_directories (${LIB_BASE_DIRECTORY})

file (GLOB ZOPER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file (GLOB ZOPER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set (CURRENT_TARGET host)

add_executable (${CURRENT_TARGET} ${ZOPER_SOURCES} ${ZOPER_HEADERS})

source_group("Header Files" FILES ${ZOPER_HEADERS})
source_group("Source Files" FILES ${ZOPER_SOURCES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set (SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")
#set(SFML_STATIC_LIBRARIES TRUE)
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
#  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${CURRENT_TARGET} ${SFML_LIBRARIES})
endif()


# Detect and add lib
include_directories(..)
target_link_libraries(${CURRENT_TARGET} lib)


add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${SFML_ROOT}/bin/$<CONFIGURATION>
	$<TARGET_FILE_DIR:${CURRENT_TARGET}>)

add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/zoper/data/
	$<TARGET_FILE_DIR:${CURRENT_TARGET}>)

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

#set(_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

#set_target_properties(${CURRENT_TARGET}
#    PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY "${_OUTPUT_DIRECTORY}"
#)

#install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION ${_OUTPUT_DIRECTORY})
#install(DIRECTORY ${SFML_ROOT}/bin/$<CONFIGURATION> DESTINATION $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
