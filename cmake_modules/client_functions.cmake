function(build_client_library)

  cmake_parse_arguments(CL_BUILD "" "DATA_SOURCE;DATA_DEST" "HEADERS;SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${CL_BUILD_SOURCES} ${CL_BUILD_HEADERS})

  # Detect and add libraries
  target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

  message("${CL_BUILD_DATA_SOURCE} Not Post build command. Copy directory")
  configure_file(app_version.hpp.in app_version.hpp @ONLY)
  include_directories(${CMAKE_CURRENT_BINARY_DIR})

  # Set defines for project versions using standard cmake nomenclature
  target_compile_definitions(${CURRENT_TARGET} PRIVATE
    ${CURRENT_TARGET}_VERSION=${PROJECT_VERSION_MAJOR}
    ${CURRENT_TARGET}_SUBVERSION=${PROJECT_VERSION_MINOR}
    ${CURRENT_TARGET}_PATCH=${PROJECT_VERSION_PATCH}
    ${CURRENT_TARGET}_TWEAK=${PROJECT_VERSION_TWEAK}
  )

  # Copy data if data directory has been passed.
  if(NOT ${CL_BUILD_DATA_SOURCE} STREQUAL "")
    message(${CL_BUILD_DATA_SOURCE})
    message("to")
    message("$<TARGET_FILE_DIR:${CURRENT_TARGET}>")

    add_custom_command(
      TARGET ${CURRENT_TARGET}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E echo "Post build command. Copy directory"
      COMMAND ${CMAKE_COMMAND} -E echo "Copy from ${CL_BUILD_DATA_SOURCE}"
      COMMAND ${CMAKE_COMMAND} -E echo "to $<TARGET_FILE_DIR:${CURRENT_TARGET}>/${CL_BUILD_DATA_DEST}"
    
      COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${CURRENT_TARGET}>/${CL_BUILD_DATA_DEST}"
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CL_BUILD_DATA_SOURCE}
              "$<TARGET_FILE_DIR:${CURRENT_TARGET}>/${CL_BUILD_DATA_DEST}")
  endif()

endfunction()
