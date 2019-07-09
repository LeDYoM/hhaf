project (lib)

include_directories ("..")

file (GLOB_RECURSE _SOURCES "board/*.cpp" "core/*.cpp" "resources/*.cpp" "scene/*.cpp" "system/*.cpp")
file (GLOB_RECURSE _HEADERS "board/*.hpp" "core/*.hpp" "include/*.hpp" "resources/*.hpp" "scene/*.hpp" "system/*.hpp")

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
target_link_libraries(${CURRENT_TARGET} PUBLIC backend_dev)

add_subdirectory(tests)
