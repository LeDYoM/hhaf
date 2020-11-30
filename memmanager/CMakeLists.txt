SET(CMAKE_INSTALL_PREFIX /home/ismael/h_test/)

project(memmanager)
cmake_minimum_required(VERSION 3.11)

set(CURRENT_TARGET memmanager)

set(SOURCES src/memmanager.cpp)
set(HEADERS memmanager/include/memmanager.hpp)

include(GenerateExportHeader)
add_library(${CURRENT_TARGET} SHARED ${SOURCES} ${HEADERS})
generate_export_header(${CURRENT_TARGET})
set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
 
 target_include_directories(${CURRENT_TARGET}
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

install(TARGETS ${CURRENT_TARGET}
        EXPORT "${CURRENT_TARGET}Targets"
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(FILES 
    ${HEADERS} 
    "${PROJECT_BINARY_DIR}/${CURRENT_TARGET}_export.h"
    DESTINATION include)
#install(FILES
# "${PROJECT_BINARY_DIR}/${CURRENT_TARGET}_export.h" DESTINATION ${INCLUDE_INSTALL_DIR}
#)
install(EXPORT "${CURRENT_TARGET}Targets"
        FILE "${CURRENT_TARGET}Targets.cmake"
        NAMESPACE "${CURRENT_TARGET}::"
        DESTINATION lib/cmake
)
