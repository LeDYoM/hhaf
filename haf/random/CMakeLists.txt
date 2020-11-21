set(_SOURCES 
    i_include/randomsystem.hpp
    src/randomnumberscomponent.cpp
    src/randomsystem.cpp)

build_internal_lib_component(SOURCES ${_SOURCES})
