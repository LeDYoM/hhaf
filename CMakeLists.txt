cmake_minimum_required (VERSION 3.8)

# Maps to a solution file (Tutorial.sln). The solution will 
# have all targets (exe, lib, dll) as projects (.vcproj)
project (Zoper)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#if(MSVC)
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
#endif(MSVC)

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
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(L3RD_PARTY_DIR "${CMAKE_SOURCE_DIR}/3rdparty")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(mtypes)
add_subdirectory(loader)
add_subdirectory(lib)
add_subdirectory(backend_sfml)
add_subdirectory(zoper)
