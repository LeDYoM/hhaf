function (prepareTestLibrary)
    include(FetchContent)
    message(STATUS "Fetching Catch2")
    #======================================

    FetchContent_Declare(CATCH2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.11.1
        CMAKE_ARGS -DBUILD_TESTING=OFF
    )

    FetchContent_MakeAvailable(Catch2)

    #======================================
    message(STATUS "Fetching Catch2 libraries done")
endfunction()

function(add_test_executable)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCE_TESTS" ${ARGN})

  prepareTestLibrary()

  foreach(NAME IN LISTS LC_BUILD_SOURCE_TESTS)
    list(APPEND SOURCE_TESTS_LIST ${NAME}.test.cpp)
  endforeach()

  add_executable(${CURRENT_TARGET} ${SOURCE_TESTS_LIST})
  
  target_link_libraries(${CURRENT_TARGET} PUBLIC Catch2)
  target_include_directories(
    ${CURRENT_TARGET} PRIVATE "${Catch2_SOURCE_DIR}/single_include/catch2")

  add_test(NAME ${CURRENT_TARGET} COMMAND ${CURRENT_TARGET})

endfunction()

function(add_haf_test_executable)

  set(PARAM_LIST ${ARGV})
  list(APPEND PARAM_LIST main)

  add_test_executable(${PARAM_LIST})

  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

endfunction(add_haf_test_executable)
