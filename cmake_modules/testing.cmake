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

    FetchContent_Declare(CATCH2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.10
        CMAKE_ARGS -DBUILD_TESTING=OFF
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

    target_link_libraries(${CURRENT_TARGET} PUBLIC Catch2)
    target_include_directories(
      ${CURRENT_TARGET} PRIVATE "${Catch2_SOURCE_DIR}/single_include/catch2")

    add_test(NAME ${CURRENT_TARGET} COMMAND ${CURRENT_TARGET})
  endif()
endfunction()

function(add_haf_test_executable)
  if (BUILD_TESTS)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/main.test.cpp"
    "#define CATCH_CONFIG_RUNNER
      #include <catch.hpp>

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

    target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
  endif()
endfunction()

function(add_test_executable_with_main)
  if (BUILD_TESTS)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/main.test.cpp"
     "#define CATCH_CONFIG_RUNNER
      #ifdef _MSC_VER
      #define CATCH_CONFIG_WINDOWS_CRTDBG
      #endif

      #pragma warning ( push )
      #pragma warning( disable : 4514 4620 4623 4625 4626 4820 5026 5027 5204 )
      #include \"catch.hpp\"
      #pragma warning ( pop )

      int main(int argc, char* argv[])
      {
        Catch::Session session;

        int returnCode = session.applyCommandLine(argc, argv);
        if (returnCode != 0)
          return returnCode;

        return session.run();
    }")

    set(PARAM_LIST ${ARGV})
    list(APPEND PARAM_LIST "${CMAKE_CURRENT_BINARY_DIR}/main")

    add_test_executable(${PARAM_LIST})

    target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
  endif()
endfunction()

function(addTestingDirectory dir)
  if (BUILD_TESTS)
    add_subdirectory(${dir})
  endif()
endfunction()
