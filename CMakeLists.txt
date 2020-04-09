# Host Application Framework
cmake_minimum_required (VERSION 3.14)
project(haf_repo
        VERSION 0.2.1
        DESCRIPTION "Host Application Framework"
#        [HOMEPAGE_URL <url-string>]
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
if(MSVC)
    add_compile_definitions(/W4 /WX)
else()
    add_compile_definitions(-Wall -Wextra -pedantic -Werror)
endif()

add_compile_definitions(HAF_COMPILE_SIMULATIONS)
add_compile_definitions(HAF_ALLOW_ACCELERATION)

message ("CXX Flags: " ${CMAKE_CXX_FLAGS})

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
include(${CMAKE_MODULE_PATH}/functions.cmake)

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(tests)
add_subdirectory(memmanager)
add_subdirectory(mtypes)
add_subdirectory(logger)
add_subdirectory(loader)
add_subdirectory(hosted_app)
add_subdirectory(host)
add_subdirectory(backend_dev)
add_subdirectory(backend)
add_subdirectory(haf)
add_subdirectory(haf_ext)
add_subdirectory(backend_sfml)
add_subdirectory(zoper_game)
add_subdirectory(librun)
