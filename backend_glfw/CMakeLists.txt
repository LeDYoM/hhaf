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

target_link_libraries(${CURRENT_TARGET} PRIVATE glfw imgui OpenGL)

#target_link_libraries(${CURRENT_TARGET} PRIVATE
#    sfml-system
#    sfml-window
#    sfml-graphics
#    renderer)

#add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
#                   COMMAND ${CMAKE_COMMAND}
#                           -E
#                           copy_directory
#                           ${SFML_BINARY_DIR}/lib
#                           $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
