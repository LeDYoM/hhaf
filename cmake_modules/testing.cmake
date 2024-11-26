macro(testing_init)
  option(BUILD_TESTS "Build test programs" ON)
  if (BUILD_TESTS)
    message("Building tests")
    enable_testing()
    prepareTestLibrary()
  else()
    message("Not building tests")
  endif()
endmacro()

function (prepareTestLibrary)
    include(FetchContent)
    message(STATUS "Fetching Catch2")
    #======================================

    set(CATCH2_COMMIT fa43b77429ba76c462b1898d6cd2f2d7a9416b14) # 3.7.1
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG ${CATCH2_COMMIT}
        CMAKE_ARGS -BUILD_SHARED_LIBS=OFF
    )

    FetchContent_MakeAvailable(Catch2)

    #======================================
    message(STATUS "Fetching Catch2 libraries done")
endfunction()

function(add_test_executable)
  if (BUILD_TESTS)
    cmake_parse_arguments(LC_BUILD "" "" "SOURCE_TESTS" ${ARGN})

    prepareTestLibrary()

    foreach(NAME IN LISTS LC_BUILD_SOURCE_TESTS)
      list(APPEND SOURCE_TESTS_LIST ${NAME}.test.cpp)
    endforeach()

    add_executable(${CURRENT_TARGET})
    target_sources(${CURRENT_TARGET} PRIVATE ${SOURCE_TESTS_LIST})
    target_compile_definitions(${CURRENT_TARGET} PUBLIC CATCH_CONFIG_ENABLE_BENCHMARKING)

    add_test(NAME ${CURRENT_TARGET} COMMAND ${CURRENT_TARGET})
  endif()
endfunction()

function(add_test_link_with_main)
  if (BUILD_TESTS)
    target_link_libraries(${CURRENT_TARGET} PUBLIC Catch2::Catch2WithMain)
  endif()
endfunction()

function(add_test_link)
  if (BUILD_TESTS)
    target_link_libraries(${CURRENT_TARGET} PUBLIC Catch2::Catch2)
  endif()
endfunction()

function(add_haf_test_executable)
  if (BUILD_TESTS)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/main.test.cpp"
    "#define CATCH_CONFIG_RUNNER
      #include <catch2/catch_test_macros.hpp>
      #include <catch2/catch_session.hpp>

      #include <hlog/include/hlog.hpp>

      int main(int argc, char* argv[])
      {
          Catch::Session session;  // There must be exactly once instance

          // writing to session.configData() here sets defaults
          // this is the preferred way to set them

          //    session.configData().showSuccessfulTests = true;
          int returnCode = session.applyCommandLine(argc, argv);
          if (returnCode != 0)  // Indicates a command line error
              return returnCode;

          // writing to session.configData() or session.Config() here
          // overrides command line args
          // only do this if you know you need to

          haf::LogInitializer log;
          return session.run();
      }
      ")

    set(PARAM_LIST ${ARGV})
    list(APPEND PARAM_LIST "${CMAKE_CURRENT_BINARY_DIR}/main")

    add_test_executable(${PARAM_LIST})
    add_test_link()
    target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
  endif()
endfunction()

function(add_test_executable_with_main)
  if (BUILD_TESTS)

    set(PARAM_LIST ${ARGV})
    list(APPEND PARAM_LIST "${CMAKE_CURRENT_BINARY_DIR}/main")

    add_test_executable(${PARAM_LIST})
    add_test_link_with_main()
    target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
  endif()
endfunction()

function(addTestingDirectory dir)
  if (BUILD_TESTS)
    add_subdirectory(${dir})
  endif()
endfunction()
