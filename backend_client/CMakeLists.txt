project (backend_client)
cmake_minimum_required (VERSION 3.14)

set (CURRENT_TARGET ${PROJECT_NAME})

set(SOURCES 
    "src/default_backend_manager.cpp")

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SOURCES})

target_compile_definitions(${CURRENT_TARGET} PRIVATE backend_client_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
