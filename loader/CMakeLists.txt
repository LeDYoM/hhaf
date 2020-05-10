project(loader)

set(CURRENT_TARGET loader)

set(SOURCES "loadedinstance.cpp" "loader.cpp" "include/loader.hpp")

add_library(${CURRENT_TARGET} SHARED ${SOURCES})
target_compile_definitions(${CURRENT_TARGET} PRIVATE loader_EXPORTS)

target_include_directories(
  ${CURRENT_TARGET}
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(${CURRENT_TARGET} ${CMAKE_DL_LIBS})

install(
  TARGETS ${CURRENT_TARGET}
  LIBRARY DESTINATION .
  RUNTIME DESTINATION .)
