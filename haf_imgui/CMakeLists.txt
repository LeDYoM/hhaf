option(use_imgui "Use Imgui" ON)

if (use_imgui)
    add_subdirectory(imgui)

    project(haf_imgui LANGUAGES C CXX)
    set(CURRENT_TARGET haf_imgui)

    set (headers haf_imgui.hpp)
    set (sources
        src/haf_imgui.cpp
        src/himgui_glfw.cpp
        src/himgui_glfw.hpp
        src/himgui_ogl3_windows.cpp
        src/himgui_ogl3_windows.hpp
        )

        build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

    target_link_libraries(${CURRENT_TARGET} PRIVATE imgui)

endif()
