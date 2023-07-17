option(use_imgui "Use Imgui" ON)

if (use_imgui AND WIN32)
    include(FetchContent)
    message(STATUS "Fetching Imggui")

    FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG master
        CMAKE_ARGS "-Wno-dev"
    )

    FetchContent_MakeAvailable(imgui)

    message("Fetching ImgGui done")
    file (GLOB HEADERS "${imgui_SOURCE_DIR}/*.h")
    file (GLOB SOURCES "${imgui_SOURCE_DIR}/*.cpp")

    message("CCCCCCCC Dir: ${imgui_SOURCE_DIR}")
    message("CCCCCCCC Sources: ${SOURCES}")
    message("CCCCCCCC Header: ${HEADERS}")
    add_library(imgui STATIC)
    target_sources(imgui PRIVATE ${SOURCES} ${HEADERS})
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

    # Add backend
    target_sources(imgui PRIVATE
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp)
endif()
