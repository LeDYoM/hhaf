project (lib)
cmake_minimum_required(VERSION 3.12)

include_directories ("..")

set(_SOURCES "main.cpp")
file (GLOB_RECURSE _HEADERS "include/*.hpp")

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

# Directory internal libraries that will be used by the client too.
add_subdirectory(render)
target_link_libraries(${CURRENT_TARGET} PRIVATE render)
add_subdirectory(resources)
target_link_libraries(${CURRENT_TARGET} PRIVATE resources)
add_subdirectory(scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
add_subdirectory(scene_components)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_components)
add_subdirectory(scene_nodes)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_nodes)
add_subdirectory(time)
target_link_libraries(${CURRENT_TARGET} PRIVATE time)
add_subdirectory(input)
target_link_libraries(${CURRENT_TARGET} PRIVATE input)
add_subdirectory(random)
target_link_libraries(${CURRENT_TARGET} PRIVATE random)
add_subdirectory(simulation)
target_link_libraries(${CURRENT_TARGET} PRIVATE simulation)
add_subdirectory(system)
target_link_libraries(${CURRENT_TARGET} PUBLIC system)
add_subdirectory(shareddata)
target_link_libraries(${CURRENT_TARGET} PRIVATE shareddata)
target_link_libraries(${CURRENT_TARGET} INTERFACE shareddata_interface)
add_subdirectory(window)
target_link_libraries(${CURRENT_TARGET} PRIVATE window)

# Internal libraries necessary for the library only.
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)

# TODO: Investigate some day
#if(MSVC)
#set_target_properties(${CURRENT_TARGET} 
#    PROPERTIES LINK_FLAGS "${LINK_FLAGS} /NODEFAULTLIB")
#endif()

add_subdirectory(tests)
