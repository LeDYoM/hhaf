project (resources CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "bmpfont.cpp"
    "bmpfontfactory.cpp"
    "shader.cpp"
    "texture.cpp"
    "ttfont.cpp"
    "ttfontinstance.cpp"
)

set (_HEADERS
    "bmpfont_private.hpp"
    "bmpfont.hpp"
    "bmpfontfactory.hpp"
    "shader.hpp"
    "texture.hpp"
    "ttfont.hpp"
    "ttfontinstance.hpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

add_library(${CURRENT_TARGET} STATIC ${_SOURCES} ${_HEADERS})
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)

target_include_directories(${CURRENT_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
