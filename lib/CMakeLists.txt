project (lib)
cmake_minimum_required(VERSION 3.11)

include_directories ("..")

file (GLOB_RECURSE _SOURCES "core/*.cpp" "resources/*.cpp" "scene/*.cpp" "system/*.cpp")
file (GLOB_RECURSE _HEADERS "core/*.hpp" "include/*.hpp" "resources/*.hpp" "scene/*.hpp" "system/*.hpp")

set (CURRENT_TARGET  ${PROJECT_NAME})

add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS})
set_target_properties(${CURRENT_TARGET}
                      PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

target_include_directories(${CURRENT_TARGET}
    PUBLIC 
#        $<INSTALL_INTERFACE:include>    
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PUBLIC backend_dev)

add_subdirectory(tests)
