option(use_system_glfw "Use system glfw instead of fetching it" OFF)

if (NOT use_system_glfw AND WIN32)

    include(FetchContent)
    message(STATUS "Fetching glfw")

    set(glfw_REQUIRED_VERSION 3.3.8)
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG ${glfw_REQUIRED_VERSION}
        CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DBUILD_SHARED_LIBS=ON
    )

    FetchContent_MakeAvailable(glfw)

#    add_subdirectory(SFML-2.5.1)

#    add_dependencies(${CURRENT_TARGET} sfml-system sfml-window sfml-graphics)

    message("Fetching glfw done")
else()
    message("Using system glfw. Note: glfw should be installed")
#    find_package(SFML 2.5 REQUIRED system window graphics)
endif()
