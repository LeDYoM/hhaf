project (resources CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/bmpfont.cpp"
    "src/bmpfont_private.hpp"
    "src/bmpfontfactory.cpp"
    "src/resourcehandler.cpp"
    "src/resourcemanager.cpp"
    "src/resourceview.cpp"
    "src/shader.cpp"
    "src/texture.cpp"
    "src/ttfont.cpp"
    "src/ttfontinstance.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    SOURCES
    ${_SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
