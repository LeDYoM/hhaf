cmake_minimum_required (VERSION 3.14)
project (mtypes CXX)

set (CURRENT_TARGET mtypes)
option(COMPILE_MTYPES_AS_SHARED "Compile mtypes as shared library" ON)

if (${COMPILE_MTYPES_AS_SHARED})
    message("SHARED: ${COMPILE_MTYPES_AS_SHARED}")
    add_library(${CURRENT_TARGET} INTERFACE)
    target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})
    target_include_directories(${CURRENT_TARGET} INTERFACE "${PROJECT_SOURCE_DIR}/mtypes/include/alloc_own/")
    target_link_libraries(${CURRENT_TARGET} INTERFACE memmanager)

else()
    message("INLINE: ${COMPILE_MTYPES_AS_SHARED}")
    add_library(${CURRENT_TARGET} INTERFACE)
    target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})
    target_include_directories(${CURRENT_TARGET} INTERFACE "${PROJECT_SOURCE_DIR}/mtypes/include/alloc_inline/")
endif()

#install (TARGETS ${CURRENT_TARGET}
#    LIBRARY DESTINATION .
#    RUNTIME DESTINATION .
#)

add_subdirectory(tests)
