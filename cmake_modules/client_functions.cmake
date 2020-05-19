function(build_client_library)

  cmake_parse_arguments(CL_BUILD "" "DATA_SOURCE" "HEADERS;SOURCES" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})

  add_library(${CURRENT_TARGET} SHARED ${CL_BUILD_SOURCES} ${CL_BUILD_HEADERS})

  set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                     true)

  # Detect and add libraries
  target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

  # Copy data if data directory has been passed.
  if(NOT ${CL_BUILD_DATA_SOURCE} STREQUAL "")
    message(VERBOSE "Post build command. Copy directory")
    message(VERBOSE ${CL_BUILD_DATA_SOURCE})
    message(VERBOSE "to")
    message(VERBOSE $<TARGET_FILE_DIR:${CURRENT_TARGET}>)

    add_custom_command(
      TARGET ${CURRENT_TARGET}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CL_BUILD_DATA_SOURCE}
              $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
  endif()

endfunction(build_client_library)
