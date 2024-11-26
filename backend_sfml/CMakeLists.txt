project(bsfml)

file(GLOB SOURCES "*.cpp" "*.hpp")

set(CURRENT_TARGET bsfml)

include (backend_client_functions)

build_concrete_backend(
    SOURCES
    ${SOURCES}
)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
target_link_libraries(${CURRENT_TARGET} PRIVATE facil_math)

# Detect and add SFML
add_subdirectory(sfml)

target_link_libraries(${CURRENT_TARGET} PRIVATE
    sfml-window
    sfml-graphics)
