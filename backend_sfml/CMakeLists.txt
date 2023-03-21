project(bsfml)

file(GLOB SOURCES "*.cpp" "*.hpp")

set(CURRENT_TARGET bsfml)

include (backend_client_functions)

build_concrete_backend(
    SOURCES
    ${SOURCES}
)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
#find_package(OpenGL REQUIRED)
#set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS} ${ASSIMP_LIBRARY} STB_IMAGE)
#target_link_libraries(${CURRENT_TARGET} PRIVATE ${OPENGL_LIBRARY})
# Detect and add SFML
add_subdirectory(sfml)

target_link_libraries(${CURRENT_TARGET} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    renderer)

#add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
#                   COMMAND ${CMAKE_COMMAND}
#                           -E
#                           copy_directory
#                           ${SFML_BINARY_DIR}/lib
#                           $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
