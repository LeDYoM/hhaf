include(FetchContent)
include(ExternalProject)
message(STATUS "Fetching third party libraries")
#======================================

set(SFML_VERSION 2.5.1)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

FetchContent_Declare(CATCH2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.11.1
    CMAKE_ARGS -DBUILD_TESTING=OFF
)

FetchContent_MakeAvailable(Catch2)

add_subdirectory(sfml)

#======================================
message(STATUS "Fetching thirdparty libraries done")
