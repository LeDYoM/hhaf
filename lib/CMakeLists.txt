project (lib)

include_directories ("..")

set(LIB_VERSION_MAJOR "1")
set(LIB_VERSION_MINOR "6")
set(LIB_VERSION_PATCH "3")

file (GLOB_RECURSE _SOURCES "board/*.cpp" "core/*.cpp" "resources/*.cpp" "scene/*.cpp" "system/*.cpp")
file (GLOB_RECURSE _HEADERS "board/*.hpp" "core/*.hpp" "include/*.hpp" "resources/*.cpp" "scene/*.hpp" "system/*.cpp")

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} ${_SOURCES} ${_HEADERS})

target_include_directories(${CURRENT_TARGET}
    PUBLIC 
#        $<INSTALL_INTERFACE:include>    
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${CURRENT_TARGET} PUBLIC memmanager)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)

add_subdirectory(tests)
