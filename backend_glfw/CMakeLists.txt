project(bglfw)

file(GLOB SOURCES "*.cpp" "*.hpp")

set(CURRENT_TARGET bglfw)

include (backend_client_functions)

build_concrete_backend(
    SOURCES
    ${SOURCES}
)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})

# Detect and add SFML
add_subdirectory(glfw)

target_link_libraries(${CURRENT_TARGET} PRIVATE glfw)
