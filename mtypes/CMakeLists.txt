set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("Minitypes"
    VERSION 0.9.1.2
    DESCRIPTION "Simple types for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

include (testing)
include (functions)
enable_testing()
set_install_dir()

set(CURRENT_TARGET mtypes)

add_library(${CURRENT_TARGET} INTERFACE)

target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})

install(
  TARGETS ${CURRENT_TARGET}
  LIBRARY DESTINATION .
  RUNTIME DESTINATION .)

add_subdirectory(tests)

build_doc(${CURRENT_TARGET})
