# Host Application Framework
project (hef)
cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#WIP (Test)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#set(BUILD_SHARED_LIBS ON)

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
if(MSVC)
    add_compile_definitions(/W4 /WX)
else()
    add_compile_definitions(-Wall -Wextra -pedantic -Werror)
endif()

add_compile_definitions(LIB_COMPILE_SIMULATIONS)
add_compile_definitions(LIB_ALLOW_ACCELERATION)
#add_compile_definitions(LIB_USE_SIMULATION_INIT_DATA)

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(L3RD_PARTY_DIR "${CMAKE_SOURCE_DIR}/3rdparty")
set(CATCH_INCLUDE_DIR  "${L3RD_PARTY_DIR}/catch2")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
include(${CMAKE_MODULE_PATH}/functions.cmake)

# Sub-directories where more CMakeLists.txt exist
#add_subdirectory(3rdparty)
add_subdirectory(memmanager)
add_subdirectory(mtypes)
add_subdirectory(logger)
add_subdirectory(loader)
add_subdirectory(hosted_app)
add_subdirectory(host)
add_subdirectory(backend_dev)
add_subdirectory(backend)
add_subdirectory(lib)
add_subdirectory(hef_ext)
add_subdirectory(backend_sfml)
add_subdirectory(zoper_game)
add_subdirectory(librun)
