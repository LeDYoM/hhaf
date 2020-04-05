project(bsfml)

file(GLOB SOURCES "*.cpp" "*.hpp")

set(CURRENT_TARGET bsfml)

build_concrete_backend(
    SOURCES
    ${SOURCES}
)

# Detect and add SFML
add_subdirectory(sfml)

add_dependencies(${CURRENT_TARGET} sfml-system sfml-window sfml-graphics)

#find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(${CURRENT_TARGET} PRIVATE sfml-system sfml-window sfml-graphics)
add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                           -E
                           copy_directory
                           ${SFML_BINARY_DIR}/lib
                           $<TARGET_FILE_DIR:${CURRENT_TARGET}>)

install(TARGETS ${CURRENT_TARGET} LIBRARY DESTINATION . RUNTIME DESTINATION .)
