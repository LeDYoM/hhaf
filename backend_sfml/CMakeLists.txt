project(bsfml)

file(GLOB SOURCES "*.cpp" "*.hpp")

set(CURRENT_TARGET bsfml)

include (backend_client_functions)

build_concrete_backend(
    SOURCES
    ${SOURCES}
)

# Detect and add SFML
add_subdirectory(sfml)

target_link_libraries(${CURRENT_TARGET} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics)

#add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
#                   COMMAND ${CMAKE_COMMAND}
#                           -E
#                           copy_directory
#                           ${SFML_BINARY_DIR}/lib
#                           $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
