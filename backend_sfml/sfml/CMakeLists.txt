option(use_system_sfml "Use system SFML instead of fetching it" OFF)

if (NOT use_system_sfml)

    include(FetchContent)
    message(STATUS "Fetching SFML")

    set(SFML_VERSION 2.5.1)

    # It's nice to get stripped-down release zips instead of cloning
    # a repo and checking out a tag
    #FetchContent_Declare(
    #  SFML
    #  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
    #)

    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG ${SFML_VERSION} #Always build with this tag, so we're sure it is stable.
        CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DBUILD_SHARED_LIBS=ON
        CMAKE_ARGS "-Wno-dev"
    )

    FetchContent_MakeAvailable(SFML)

#    add_subdirectory(SFML-2.5.1)

    add_dependencies(${CURRENT_TARGET} sfml-system sfml-window sfml-graphics)

    message("Fetching SFML done")
else()
    message("Using system SFML. Note: SFML should be installed")
    find_package(SFML 2.5 REQUIRED system window graphics)
endif()
