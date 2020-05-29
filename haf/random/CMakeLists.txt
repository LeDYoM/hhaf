project(random CXX)
cmake_minimum_required(VERSION 3.12)

set(_SOURCES "i_include/randomsystem.hpp" "src/randomnumberscomponent.cpp"
             "src/randomsystem.cpp")

set(CURRENT_TARGET ${PROJECT_NAME})

set(INTERNAL_TARGET random)
set(_LINK_PRIVATE scene system_internal)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})

target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE system_internal)
