cmake_minimum_required(VERSION 3.14)
project(backend)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCES "src/backend_creator.cpp" "src/backendfactory.cpp"
            "src/backendregister.cpp")

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SOURCES})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_client)

