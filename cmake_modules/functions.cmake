macro(setOptions)
  option(BUILD_TESTS "Build test programs" ON)
  option(BUILD_PACKAGES "Build packages" ON)
  option(BUILD_DOCS "Build docs" OFF)
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

  cmake_parse_arguments(LC_BUILD "EXPORT_ALL;STATIC" "HEADER_DIRECTORY" "SOURCES;HEADERS"
                        ${ARGN})

  if(LC_BUILD_STATIC)
    message(STATUS "Add library static: ${CURRENT_TARGET}")
    add_library(${CURRENT_TARGET} STATIC ${LC_BUILD_SOURCES})
  else()
    message(STATUS "Add library shared: ${CURRENT_TARGET}")
    add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})
  endif()

  target_sources(${CURRENT_TARGET} PRIVATE "${SOURCES};${HEADERS}")
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

  set_target_properties(${CURRENT_TARGET}
    PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
  )

  include(GNUInstallDirs)
  install(TARGETS ${target}
    EXPORT ${target}_targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

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
    set(DOXYGEN_EXCLUDE_PATTERNS 
      */.git/*
      */build/*
    */tests/*)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)

    find_package(Doxygen REQUIRED)

    doxygen_add_docs(
        docs
        ${module_list} README.md
        ALL
        COMMENT "Generate html pages for the framework"
    )
  endif()
endfunction()

function(set_install_options_for_target target)
endfunction()

function(generate_package module_list)
  message("Preparing package for ${PROJECT_NAME}")

  message("Generating install for module list: ${module_list}")
  # Common properties
  foreach(target ${module_list})
    set_install_options_for_target(${target})
  endforeach()

  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
  set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
  set(CPACK_PACKAGE_VENDOR "Ismael Gonzalez Burgos")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
  set(CPACK_PACKAGE_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})
  message("Package version: ${CPACK_PACKAGE_VERSION}")

  if(WIN32)
      message("Packaging ${PROJECT_NAME} for Windows")
      set(CPACK_GENERATOR "ZIP")
  else()
      message("Packaging ${PROJECT_NAME} for DEB")
      set(CPACK_GENERATOR "DEB")
      set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
      set(CPACK_DEBIAN_FILE_NAME "${PROJECT_NAME}.deb")
  endif()
  include(CPack)
endfunction()
