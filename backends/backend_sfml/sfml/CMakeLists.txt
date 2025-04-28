if(LINUX)
    option(use_system_sfml "Use system SFML instead of fetching it" ON)
else()
    option(use_system_sfml "Use system SFML instead of fetching it" OFF)
endif()

if (NOT use_system_sfml)

    include(FetchContent)
    message(STATUS "Fetching SFML")

    set(SFML_VERSION 5383d2b3948f805af55c9f8a4587ac72ec5981d1) #2.6.2

    # It's nice to get stripped-down release zips instead of cloning
    # a repo and checking out a tag
    #FetchContent_Declare(
    #  SFML
    #  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
    #)

    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG ${SFML_VERSION}
        CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS=ON
    )

    FetchContent_MakeAvailable(SFML)

    message("Fetching SFML done")
else()
    message("Using system SFML. Note: SFML should be installed")
    find_package(SFML 2.5 REQUIRED system window graphics)
endif()

option(use_imgui "Use ImGUI" OFF)
message("Use ImGUI: ${use_imgui}")

if(use_imgui)
    if(LINUX)
        option(use_system_imgui "Use system ImGUI instead of fetching it" ON)
    else()
        option(use_system_imgui "Use system ImGUI instead of fetching it" OFF)
    endif()

    target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_USE_SFML_IMGUI)
    target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_USE_IMGUI)

    if (NOT use_system_imgui)

        include(FetchContent)
        message(STATUS "Fetching ImGUI")

        set(IMGUI_VERSION 97428e8ac99e339ce05eee531cf55b77b29ea709) #v1.91.9

        FetchContent_Declare(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui
            GIT_TAG ${IMGUI_VERSION}
            CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS=ON
        )
        FetchContent_MakeAvailable(imgui)

    endif()

    message(STATUS "Fetching ImGUI-SFML")
    set(IMGUI_SFML_VERSION 64e09feda29266572799e5ded66eac5cb0a749aa) #v2.6.1

    FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG ${IMGUI_SFML_VERSION}
        CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS=ON
    )

    set(IMGUI_DIR ${imgui_SOURCE_DIR})
    option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
    option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)
    FetchContent_MakeAvailable(imgui-sfml)
endif()
