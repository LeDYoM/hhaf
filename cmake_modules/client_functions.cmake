function(build_client_library)

  cmake_parse_arguments(CL_BUILD "" "DATA_SOURCE" "HEADERS;SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${CL_BUILD_SOURCES} ${CL_BUILD_HEADERS})

  # Detect and add libraries
  target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

  message("${CL_BUILD_DATA_SOURCE} Not Post build command. Copy directory")
  configure_file(app_version.hpp.in app_version.hpp @ONLY)
  include_directories(${CMAKE_CURRENT_BINARY_DIR})

  # Copy data if data directory has been passed.
  if(NOT ${CL_BUILD_DATA_SOURCE} STREQUAL "")
    message("Post build command. Copy directory")
    message(${CL_BUILD_DATA_SOURCE})
    message("to")
    message("$<TARGET_FILE_DIR:${CURRENT_TARGET}>")

    add_custom_command(
      TARGET ${CURRENT_TARGET}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CL_BUILD_DATA_SOURCE}
              $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
  endif()

endfunction(build_client_library)
