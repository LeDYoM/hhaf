
include_directories (${LIB_BASE_DIRECTORY})

file (GLOB ZOPER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file (GLOB ZOPER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set (CURRENT_TARGET host)

add_executable (${CURRENT_TARGET} ${ZOPER_SOURCES} ${ZOPER_HEADERS})

source_group("Header Files" FILES ${ZOPER_HEADERS})
source_group("Source Files" FILES ${ZOPER_SOURCES})


# Detect and add lib
include_directories(..)
target_link_libraries(${CURRENT_TARGET} PRIVATE lib)

#Temp
include_directories(../backend_sfml)
target_link_libraries(${CURRENT_TARGET} PRIVATE bsfml)

target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)

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

install (TARGETS ${CURRENT_TARGET} DESTINATION  .)
install(DIRECTORY ${SFML_ROOT}/bin/$<CONFIGURATION>/ DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/zoper/data/ DESTINATION .)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "Zoper")
SET(CPACK_PACKAGE_VENDOR "LeDYoM")
set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
