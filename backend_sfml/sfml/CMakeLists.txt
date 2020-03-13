include(FetchContent)
include(ExternalProject)
message(STATUS "Fetching third party libraries")
#======================================

set(SFML_VERSION 2.5.1)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
#FetchContent_Declare(
#  SFML
#  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
#)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1 #Always build with this tag, so we're sure it is stable.
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DBUILD_SHARED_LIBS=ON
)

FetchContent_MakeAvailable(SFML)

# No need to build audio and network modules
#add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)

#======================================
message(STATUS "Fetching thirdparty libraries done")
