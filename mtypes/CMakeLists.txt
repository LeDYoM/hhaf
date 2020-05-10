cmake_minimum_required(VERSION 3.14)
project(mtypes CXX)

set(CURRENT_TARGET mtypes)

add_library(${CURRENT_TARGET} INTERFACE)
target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})

if(${MTYPES_USE_MEMMANAGER})
  target_include_directories(
    ${CURRENT_TARGET}
    INTERFACE "${PROJECT_SOURCE_DIR}/mtypes/include/alloc_own/")
  target_link_libraries(${CURRENT_TARGET} INTERFACE memmanager)
else()
  target_include_directories(
    ${CURRENT_TARGET}
    INTERFACE "${PROJECT_SOURCE_DIR}/mtypes/include/alloc_inline/")
endif()

install(
  TARGETS ${CURRENT_TARGET}
  LIBRARY DESTINATION .
  RUNTIME DESTINATION .)

add_subdirectory(tests)
