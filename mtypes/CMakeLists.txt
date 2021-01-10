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
set(CURRENT_TARGET mtypes)

add_library(${CURRENT_TARGET} INTERFACE)
#set_cxx_standard(${CURRENT_TARGET})
target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})

set(base_directory mtypes/include)

if(${MTYPES_USE_MEMMANAGER})
    message(STATUS "Linking ${CURRENT_TARGET} against memmanager")
    target_include_directories(
        ${CURRENT_TARGET}
        INTERFACE "${base_directory}/alloc_own")
      target_link_libraries(${CURRENT_TARGET} INTERFACE memmanager)
else()
    message(STATUS "${CURRENT_TARGET} is not using any 3rd party memmanager")
    target_include_directories(
        ${CURRENT_TARGET}
        INTERFACE "${base_directory}/alloc_inline")
endif()

install(
  TARGETS ${CURRENT_TARGET}
  LIBRARY DESTINATION .
  RUNTIME DESTINATION .)

add_subdirectory(tests)

build_doc(${CURRENT_TARGET})
