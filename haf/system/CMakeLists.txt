project(system CXX)
cmake_minimum_required(VERSION 3.12)

set(_SOURCES
    "i_include/appservice.hpp"
    "i_include/get_system.hpp"
    "i_include/get_systemprovider.hpp"
    "i_include/systemcontroller.hpp"
    "i_include/systemprovider.hpp"
    "src/appservice.cpp"
    "src/get_systemprovider.cpp"
    "src/get_system.cpp"
    "src/systemaccess.cpp"
    "src/systemcontroller.cpp"
    "src/systemprovider.cpp"
    "src/systemprovider_init.cpp")

set(CURRENT_TARGET ${PROJECT_NAME})

set(INTERNAL_TARGET system)
set(_LINK_PRIVATE
    backend
    backend_dev
    filesystem
    hosted_app
    input
    random
    render
    resources
    scene
    scene_internal
    shareddata
    simulation
    time
    window)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})

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
