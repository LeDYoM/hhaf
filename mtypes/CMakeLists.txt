cmake_minimum_required (VERSION 3.14)
project (mtypes CXX)

set (CURRENT_TARGET mtypes)

add_library(${CURRENT_TARGET} INTERFACE)
target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})

install (TARGETS ${CURRENT_TARGET}
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)

add_subdirectory(tests)
