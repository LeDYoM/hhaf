project (libef)
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
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(L3RD_PARTY_DIR "${CMAKE_SOURCE_DIR}/3rdparty")
set(CATCH_INCLUDE_DIR  "${L3RD_PARTY_DIR}/catch2")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(memmanager)
add_subdirectory(mtypes)
add_subdirectory(logger)
add_subdirectory(loader)
add_subdirectory(host)
add_subdirectory(backend_dev)
add_subdirectory(backend)
add_subdirectory(lib)
add_subdirectory(backend_sfml)
add_subdirectory(zoper_game)
add_subdirectory(librun)
