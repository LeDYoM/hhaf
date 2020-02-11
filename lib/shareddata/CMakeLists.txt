project (shareddata CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/shareddatasystem.cpp"
    "src/shareddataview.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${_SOURCES}
)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
