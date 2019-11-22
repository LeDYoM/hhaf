project(zoper_game)
cmake_minimum_required(VERSION 3.11)

file (GLOB_RECURSE HEADERS "*.hpp")
file (GLOB_RECURSE SOURCES "*.cpp")

set (CURRENT_TARGET  ${PROJECT_NAME})

build_client_library(
    DATA_SOURCE "${PROJECT_SOURCE_DIR}/../zoper_data/"
    HEADERS 
    ${HEADERS}
    
    SOURCES
    ${SOURCES})

target_compile_definitions(${CURRENT_TARGET} PRIVATE USE_DEBUG_ACTIONS)

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
