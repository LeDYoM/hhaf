project (lib)

set(SOURCE_FILES_LIST
    backend/backendfactory.cpp
    backend/backendfactory.hpp
    backend/interfaces.hpp
    backend/itexturefactory.hpp
    backend/itexture.hpp
    backend/ittfontfactory.hpp
    backend/ittfont.hpp
    backend/iwindow.hpp

    board/boardmodel.cpp
    board/boardmodel.hpp
    board/itilescontroller.hpp
)

#Add all the file from the library to compile
file (GLOB_RECURSE LIB_HEADERS "*.hpp")
file (GLOB_RECURSE LIB_SOURCES "*.cpp")

include_directories ("..")

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LIB_HEADERS} ${LIB_SOURCES})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
