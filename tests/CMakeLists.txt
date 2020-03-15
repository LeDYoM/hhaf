include(FetchContent)
message(STATUS "Fetching Catch2")
#======================================

FetchContent_Declare(CATCH2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.11.1
    CMAKE_ARGS -DBUILD_TESTING=OFF
)

FetchContent_MakeAvailable(Catch2)

#======================================
message(STATUS "Fetching Catch2 libraries done")
