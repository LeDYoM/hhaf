project(host)
cmake_minimum_required(VERSION 3.11)

set(CURRENT_TARGET host)

set(SOURCES "src/apploader.cpp" "src/host.cpp" "src/main.cpp")

add_library(${CURRENT_TARGET} SHARED ${SOURCES})
set_target_properties(${CURRENT_TARGET}
                      PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${CURRENT_TARGET} PUBLIC memmanager)
target_link_libraries(${CURRENT_TARGET} PRIVATE lib)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE lib)

target_link_libraries(${CURRENT_TARGET} PRIVATE zoper_game)
