FetchContent_GetProperties(SFML)

if(NOT SFML_POPULATED)
    FetchContent_Populate(SFML)

    add_subdirectory(${SFML_SOURCE_DIR} ${SFML_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
