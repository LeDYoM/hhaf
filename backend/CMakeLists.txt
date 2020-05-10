project(backend)
cmake_minimum_required(VERSION 3.11)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCES "src/backend_creator.cpp" "src/backendfactory.cpp"
            "src/backendregister.cpp")

add_library(${CURRENT_TARGET} SHARED ${SOURCES})
set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                   true)

target_include_directories(
  ${CURRENT_TARGET}
  PUBLIC # $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
