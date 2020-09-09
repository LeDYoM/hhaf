cmake_minimum_required(VERSION 3.14)
project(
  "basic_app_loader"
  VERSION 0.1.1.1
  DESCRIPTION "HAF Application loader"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

file (GLOB_RECURSE HEADERS "*.hpp")
file (GLOB_RECURSE SOURCES "*.cpp")

set (CURRENT_TARGET ${PROJECT_NAME})

include(client_functions)

build_client_library(

#    DATA_SOURCE "${PROJECT_SOURCE_DIR}/../zoper_data/"

    HEADERS 
    ${HEADERS}
    
    SOURCES
    ${SOURCES}
)

# Extension libraries
target_link_libraries(${CURRENT_TARGET} PRIVATE haf_user)
#target_link_libraries(${CURRENT_TARGET} PRIVATE boardmanager)
#target_link_libraries(${CURRENT_TARGET} PRIVATE menu_paged)

#target_compile_definitions(${CURRENT_TARGET} PRIVATE USE_DEBUG_ACTIONS)
#target_compile_definitions(${CURRENT_TARGET} PRIVATE TEST_BMP_FONT)

#install(TARGETS ${CURRENT_TARGET} DESTINATION  .)
#install(DIRECTORY ${SFML_ROOT}/bin/$<CONFIGURATION>/ DESTINATION .)
#install(DIRECTORY ${PROJECT_SOURCE_DIR}/zoper/data/ DESTINATION .)
