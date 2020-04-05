function(build_client_library)

    cmake_parse_arguments(CL_BUILD "" "DATA_SOURCE" "HEADERS;SOURCES" ${ARGN})

    set (CURRENT_TARGET ${PROJECT_NAME})

    add_library (${CURRENT_TARGET} SHARED ${CL_BUILD_SOURCES} ${CL_BUILD_HEADERS})

    set_target_properties(${CURRENT_TARGET}
                        PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

    # Detect and add libraries
    target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
    target_link_libraries(${CURRENT_TARGET} PRIVATE lib)
    target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
    target_link_libraries(${CURRENT_TARGET} PRIVATE logger)

    # Copy data if data directory has been passed.
    if (NOT ${CL_BUILD_DATA_SOURCE} STREQUAL "")
        message(VERBOSE "Post build command. Copy directory")
        message(VERBOSE ${CL_BUILD_DATA_SOURCE})
        message(VERBOSE "to")
        message(VERBOSE $<TARGET_FILE_DIR:${CURRENT_TARGET}>)

        add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CL_BUILD_DATA_SOURCE}
                $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
    endif()

endfunction(build_client_library)

# Function to build different components from the project in an unified way.
function(build_lib_component)

    cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "SOURCES" ${ARGN})

    set (CURRENT_TARGET ${PROJECT_NAME})

    add_library (${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})

    set_target_properties(${CURRENT_TARGET}
                      PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

    target_include_directories(${CURRENT_TARGET} PUBLIC ${LC_BUILD_HEADER_DIRECTORY})

endfunction(build_lib_component)

# Function to build different components from the project in an unified way.
function(build_lib_interface_component)

    cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "" ${ARGN})

    set (CURRENT_TARGET ${PROJECT_NAME})

    add_library (${CURRENT_TARGET} INTERFACE)
    target_include_directories(${CURRENT_TARGET} INTERFACE ${LC_BUILD_HEADER_DIRECTORY})

    install (TARGETS ${CURRENT_TARGET}
        LIBRARY DESTINATION .
        RUNTIME DESTINATION .
    )

endfunction(build_lib_interface_component)

# Function to build different components from the project in an unified way.
function(build_internal_lib_component)

    cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "SOURCES" ${ARGN})

    set (CURRENT_TARGET ${PROJECT_NAME})
    set(_PUBLIC_INCLUDE "/include")
    set(_PUBLIC_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}${_PUBLIC_INCLUDE}")
    set(_INTERNAL_INCLUDE "/i_include")
    set(_INTERNAL_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}${_INTERNAL_INCLUDE}")

    add_library (${CURRENT_TARGET} STATIC ${LC_BUILD_SOURCES} ${_PUBLIC_INCLUDE_DIRECTORY})

# As long as static libraries are used for internal components, we do not need this.
#    set_target_properties(${CURRENT_TARGET}
#                      PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

    target_include_directories(${CURRENT_TARGET} 
        PUBLIC
        ${_PUBLIC_INCLUDE_DIRECTORY}
        ${_INTERNAL_INCLUDE_DIRECTORY}
        )

    add_library (${CURRENT_TARGET}_interface INTERFACE)
    target_include_directories(${CURRENT_TARGET}_interface INTERFACE ${_PUBLIC_INCLUDE_DIRECTORY})

    target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
    target_link_libraries(${CURRENT_TARGET} PRIVATE logger)

endfunction(build_internal_lib_component)

# Function to build different components from the project in an unified way.
function(build_concrete_backend)

    cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

    add_library(${CURRENT_TARGET} SHARED ${SOURCES})

    # Patch for testing TO DO: Remove it (use a variable)
    include_directories("..")

    target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
    target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)

endfunction(build_concrete_backend)

function(add_test_executable)

    cmake_parse_arguments(LC_BUILD "" "" "SOURCE_TESTS" ${ARGN})

    include(FetchContent)
    FetchContent_MakeAvailable(Catch2)

    foreach(NAME IN LISTS SOURCE_TESTS)
        list(APPEND SOURCE_TESTS_LIST ${NAME}.test.cpp)
    endforeach()

    enable_testing()
    add_executable(${CURRENT_TARGET} ${SOURCE_TESTS_LIST})

    target_link_libraries(${CURRENT_TARGET} PUBLIC Catch2)
    target_include_directories(${CURRENT_TARGET} 
        PRIVATE "${Catch2_SOURCE_DIR}/single_include/catch2")

endfunction(add_test_executable)
