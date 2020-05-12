project (window CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/window.cpp"
    "src/window_properties.cpp"
    )

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${_SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE input_internal)
target_link_libraries(${CURRENT_TARGET} PRIVATE render_internal)