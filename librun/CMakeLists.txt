project(librun)

file (GLOB_RECURSE _HEADERS "*.hpp")
file (GLOB_RECURSE _SOURCES "*.cpp")

set (CURRENT_TARGET librun)

add_executable (${CURRENT_TARGET} ${_SOURCES} ${_HEADERS})

# Detect and add lib
include_directories(..)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE lib)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE zoper_game)

install (TARGETS ${CURRENT_TARGET} DESTINATION  .)
install(DIRECTORY ${SFML_ROOT}/bin/$<CONFIGURATION>/ DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/zoper/data/ DESTINATION .)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "LibRun")
SET(CPACK_PACKAGE_VENDOR "LeDYoM")
set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
