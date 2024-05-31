include(FetchContent)
message(STATUS "Fetching Imggui")

set(IMGUI_COMMIT 9d8de45)
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG ${IMGUI_COMMIT}
    CMAKE_ARGS "-Wno-dev"
)

FetchContent_MakeAvailable(imgui)

message("Fetching ImgGui done")
file (GLOB HEADERS "${imgui_SOURCE_DIR}/*.h")
file (GLOB SOURCES "${imgui_SOURCE_DIR}/*.cpp")

add_library(imgui STATIC)
target_sources(imgui PRIVATE ${SOURCES} ${HEADERS})
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

# Add backend
target_sources(imgui PRIVATE
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
    )

target_link_libraries(imgui PUBLIC glfw)