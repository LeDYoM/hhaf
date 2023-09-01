option(use_imgui "Use Imgui" ON)

if (use_imgui)
    add_subdirectory(imgui)

    project(haf_imgui LANGUAGES C CXX)
    set(CURRENT_TARGET haf_imgui)

    set (headers haf_imgui.hpp)
    set (sources src/haf_imgui.cpp)
    build_lib_component(STATIC HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

    target_link_libraries(${CURRENT_TARGET} PUBLIC imgui)

endif()
