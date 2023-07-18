option(use_imgui "Use Imgui" ON)

if (use_imgui)
    add_subdirectory(imgui)

    project(haf_imgui LANGUAGES C CXX)
    set(current_target haf_imgui)

    set (headers haf_imgui.hpp)
    set (sources src/haf_imgui.cpp)
    add_library(${current_target} STATIC)
    target_sources(${current_target} PRIVATE ${sources} ${headers})
    target_include_directories(${current_target} PUBLIC ${PROJECT_SOURCE_DIR})

    target_link_libraries(${current_target} PUBLIC imgui)

endif()
