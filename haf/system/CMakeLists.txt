project (system CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES
    "src/appservice.cpp"
    "src/get_systemprovider.cpp"
    "src/get_system.cpp"
    "src/systemaccess.cpp"
    "src/systemprovider.cpp"
    "src/systemprovider_init.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${_SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE filesystem)
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE input)
target_link_libraries(${CURRENT_TARGET} PRIVATE random)
target_link_libraries(${CURRENT_TARGET} PRIVATE render)
target_link_libraries(${CURRENT_TARGET} PRIVATE resources)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_internal)
target_link_libraries(${CURRENT_TARGET} PRIVATE shareddata)
target_link_libraries(${CURRENT_TARGET} PRIVATE simulation)
target_link_libraries(${CURRENT_TARGET} PRIVATE time)
target_link_libraries(${CURRENT_TARGET} PRIVATE window)
