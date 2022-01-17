cmake_minimum_required(VERSION 3.14)
project(
  "haf_app_menu"
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

target_link_libraries(${CURRENT_TARGET} PRIVATE haf_user)
