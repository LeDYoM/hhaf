cmake_minimum_required(VERSION 3.14)
project(
  "Zoper"
  VERSION 1.5.1.2
  DESCRIPTION "Zoper game"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

file (GLOB_RECURSE HEADERS "*.hpp")
file (GLOB_RECURSE SOURCES "*.cpp")

set (CURRENT_TARGET ${PROJECT_NAME})

include(client_functions)

build_client_library(

    DATA_SOURCE "${PROJECT_SOURCE_DIR}/../zoper_data/"

    DATA_DEST "."
    HEADERS 
    ${HEADERS}
    
    SOURCES
    ${SOURCES}
)

# Extension libraries
target_link_libraries(${CURRENT_TARGET} PRIVATE haf_user)
target_link_libraries(${CURRENT_TARGET} PRIVATE boardmanager)
target_link_libraries(${CURRENT_TARGET} PRIVATE menu_paged)

target_compile_definitions(${CURRENT_TARGET} PRIVATE USE_DEBUG_ACTIONS)
#target_compile_definitions(${CURRENT_TARGET} PRIVATE TEST_BMP_FONT)

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
