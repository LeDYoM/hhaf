project(zoper_game)
cmake_minimum_required(VERSION 3.11)

file (GLOB_RECURSE HEADERS "*.hpp")
file (GLOB_RECURSE SOURCES "*.cpp")

set (CURRENT_TARGET  ${PROJECT_NAME})

add_library (${CURRENT_TARGET} SHARED ${SOURCES} ${HEADERS})
set_target_properties(${CURRENT_TARGET}
                      PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

# Detect and add libraries
target_link_libraries(${CURRENT_TARGET} PRIVATE lib)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)

add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/../zoper_data/
    $<TARGET_FILE_DIR:${CURRENT_TARGET}>)

install(TARGETS ${CURRENT_TARGET} DESTINATION  .)
install(DIRECTORY ${SFML_ROOT}/bin/$<CONFIGURATION>/ DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/zoper/data/ DESTINATION .)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
#set(CPACK_PACKAGE_NAME "Zoper")
#SET(CPACK_PACKAGE_VENDOR "LeDYoM")
#set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
#set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
#include(CPack)
