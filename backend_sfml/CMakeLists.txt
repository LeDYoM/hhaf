project(bsfml)

file(GLOB _SOURCES "*.cpp")
file(GLOB _HEADERS "*.hpp")

set(CURRENT_TARGET bsfml)

add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS})

# Patch for testing TO DO: Remove it (use a variable)
include_directories("..")

target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)

# Detect and add SFML

# Set fallback directory for SFML
set(SFML_ROOT "${L3RD_PARTY_DIR}/SFML")

add_subdirectory(sfml)
#FetchContent_GetProperties(SFML)

## In most cases better set in the CMake cache
set(SFML_DIR "${SFML_BINARY_DIR}")

# Find any version 2.X of SFML See the FindSFML.cmake file for additional
# details and instructions
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(${CURRENT_TARGET} PRIVATE sfml-system sfml-window sfml-graphics)
add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                           -E
                           copy_directory
                           ${SFML_BINARY_DIR}/lib
                           $<TARGET_FILE_DIR:${CURRENT_TARGET}>)

install(TARGETS ${CURRENT_TARGET} LIBRARY DESTINATION . RUNTIME DESTINATION .)
