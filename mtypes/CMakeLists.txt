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

set(CURRENT_TARGET mtypes)

add_library(${CURRENT_TARGET} INTERFACE)

target_include_directories(${CURRENT_TARGET}
    INTERFACE 
        $<INSTALL_INTERFACE:.>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

file(GLOB public_headers 
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/${CURRENT_TARGET}/include/*.hpp
  )

set_target_properties(${CURRENT_TARGET} PROPERTIES PUBLIC_HEADER "${public_headers}")

install(
  TARGETS ${CURRENT_TARGET}
  PUBLIC_HEADER DESTINATION ${CURRENT_TARGET}/include
  )

add_subdirectory(tests)

build_doc(${CURRENT_TARGET})

if(${BUILD_PACKAGE_FOR} STREQUAL ${CURRENT_TARGET})
  message("Preparing package for mtypes")
  # Common properties
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
  set(CPACK_PACKAGE_NAME ${CURRENT_TARGET})
  set(CPACK_PACKAGE_VENDOR "Ismael Gonzalez Burgos")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
  message("Package version: ${CPACK_PACKAGE_VERSION}")
  if(WINDOWS)
      message("Packaginf ${CURRENT_TARGET} for Windows")
      set(CPACK_GENERATOR "ZIP")
  else()
      message("Packaging ${CURRENT_TARGET} for DEB")
      set(CPACK_GENERATOR "DEB")
      set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
      set(CPACK_DEBIAN_FILE_NAME "${CURRENT_TARGET}.deb")
  endif()
  include(CPack)
endif()
