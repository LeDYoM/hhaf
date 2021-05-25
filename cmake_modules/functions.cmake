macro(setOptions)
  option(BUILD_TESTS "Build test programs" ON)
  option(BUILD_PACKAGES "Build packages" OFF)
  option(BUILD_DOCS "Build docs" ON)
endmacro()

macro(includeForOptions)
  if (BUILD_TESTS)
    message("Building tests")
    enable_testing()
    include(testing)
    add_subdirectory(tests)
  else()
    message("Not building tests")
  endif()

  if(BUILD_PACKAGES)
    include(install)
    message("Building packages")
  else()
    message("Not building packages")
  endif()

  if(BUILD_DOCS)
    message("Building documentation")
  else()
    message("Not building documentation")
  endif()
endmacro()

function(set_cxx_standard CURRENT_TARGET)
    set_target_properties(${CURRENT_TARGET} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON)
endfunction()

function(set_output_directories CURRENT_TARGET)
  set_target_properties(${CURRENT_TARGET}
    PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endfunction()

function (set_compile_warning_level CURRENT_TARGET level)
    target_compile_options(${CURRENT_TARGET} ${level}
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>
    )
endfunction()

function (set_compile_warning_level_interface CURRENT_TARGET)
    set_compile_warning_level(${CURRENT_TARGET} INTERFACE)
endfunction()

function(set_compile_warning_level_and_cxx_properties CURRENT_TARGET)
    set_compile_warning_level(${CURRENT_TARGET} PRIVATE)
    set_cxx_standard(${CURRENT_TARGET})
endfunction()

# Function to build different components from the project in an unified way.
function(build_lib_component)

  cmake_parse_arguments(LC_BUILD "EXPORT_ALL;STATIC" "HEADER_DIRECTORY" "SOURCES"
                        ${ARGN})

  if(LC_BUILD_STATIC)
    message(STATUS "Add library static: ${CURRENT_TARGET}")
    add_library(${CURRENT_TARGET} STATIC ${LC_BUILD_SOURCES})
  else()
    message(STATUS "Add library shared: ${CURRENT_TARGET}")
    add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})
  endif()

  set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})
  set_output_directories(${CURRENT_TARGET})

  if(LC_BUILD_EXPORT_ALL)
    if (LC_BUILD_STATIC)
      message(WARN "STATIC and EXPORT_ALL together makes no sense")
    endif()
    set_target_properties(${CURRENT_TARGET}
                          PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
  endif()

  target_include_directories(${CURRENT_TARGET}
      PUBLIC
      "$<INSTALL_INTERFACE:include>"
      "$<BUILD_INTERFACE:${LC_BUILD_HEADER_DIRECTORY}>"
  )

  file(GLOB_RECURSE public_headers 
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${CURRENT_TARGET}/include/*.hpp
    )

  include(GNUInstallDirs)
  install(TARGETS ${CURRENT_TARGET}
      EXPORT ${CURRENT_TARGET}Targets
      INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

#  install(EXPORT ${CURRENT_TARGET}Targets
#    FILE ${CURRENT_TARGET}Targets.cmake
#    NAMESPACE hhaf::
#  DESTINATION
#    ${CMAKE_INSTALL_LIBDIR}/cmake/hhaf)

endfunction()


function(build_lib_ext)

  cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "SOURCES" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})

  add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})

  set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                     true)

  target_include_directories(${CURRENT_TARGET}
                             PUBLIC ${LC_BUILD_HEADER_DIRECTORY})
  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

endfunction()

# Function to build different components from the project in an unified way.
function(build_lib_interface_component)

  cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "SOURCES" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})

  add_library(${CURRENT_TARGET} INTERFACE)
  target_sources(${CURRENT_TARGET} INTERFACE ${LC_BUILD_SOURCES})
  target_include_directories(${CURRENT_TARGET}
                             INTERFACE ${LC_BUILD_HEADER_DIRECTORY})

  export(TARGETS ${CURRENT_TARGET} FILE ${CURRENT_TARGET}_target.cmake)

endfunction()

# Function to build different components from the project in an unified way.
function(build_concrete_backend)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${SOURCES})
  target_link_libraries(${CURRENT_TARGET} PRIVATE log_and_types)
  target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
  target_link_libraries(${CURRENT_TARGET} PRIVATE backend_client)

endfunction()

function(build_docs module_list)
  if(BUILD_DOCS)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_EXCLUDE build;tests)

    find_package(Doxygen REQUIRED)

    doxygen_add_docs(
        docs
        ${module_list}
        ${PROJECT_SOURCE_DIR}
        ALL
        COMMENT "Generate html pages for the framework"
    )
  endif()
endfunction()

macro(stardard_install_package)
    if(${BUILD_PACKAGE_FOR})
        if("${BUILD_PACKAGE_FOR}" STREQUAL "${CURRENT_TARGET}")
        message("Preparing package for ${CURRENT_TARGET}")

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
    endif()
endmacro()

macro(stardard_install_haf)
  set(CPACK_PACKAGE_VERSION_MAJOR "1")
  set(CPACK_PACKAGE_VERSION_MINOR "0")
  set(CPACK_PACKAGE_VERSION_PATCH "0")
  set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

  message("Package version: ${CPACK_PACKAGE_VERSION}")

  set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
  set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "HAF main package")
  set(CPACK_GENERATOR "DEB")
  set(author_ "Ismael Gonzalez Burgos")
  set(CPACK_PACKAGE_VENDOR ${author_})
  set(CPACK_SET_DESTDIR "ON")  # Necessary because of the absolute install paths

  if(WINDOWS)
    message("Packaginf ${CURRENT_TARGET} for Windows")
    set(CPACK_GENERATOR "ZIP")
  else()
    message("Packaging ${CURRENT_TARGET} for DEB")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
  endif()

  include(CPack)
endmacro()

macro(stardard_install_haf2)
        message("Preparing package for hhaf")

        # Common properties
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "HAF main package")
        set(CPACK_PACKAGE_NAME "hhaf")
        set(CPACK_PACKAGE_VERSION_MAJOR "1")
        set(CPACK_PACKAGE_VERSION_MINOR "0")
        set(CPACK_PACKAGE_VERSION_PATCH "0")
        set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
        message("Package version: ${CPACK_PACKAGE_VERSION}")
#        set(CPACK_INSTALL_CMAKE_PROJECTS "ALL")
        if(WINDOWS)
            message("Packaginf ${CURRENT_TARGET} for Windows")
            set(CPACK_GENERATOR "ZIP")
        else()
            message("Packaging ${CURRENT_TARGET} for DEB")
            set(CPACK_GENERATOR "DEB")
            set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
            set(CPACK_DEBIAN_FILE_NAME "${CURRENT_TARGET}.deb")
        endif()
        set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}
          #-${CPACK_SYSTEM_NAME}
          )
        message("CPACK_PACKAGE_FILE_NAME: ${CPACK_PACKAGE_FILE_NAME}")
        include(CPack)
#        endif()
#    endif()
endmacro()
