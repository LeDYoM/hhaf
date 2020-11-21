set(_SOURCES
    i_include/inputsystem.hpp
    src/input_component_base.cpp
    src/inputcomponent.cpp
    src/inputdriver.cpp
    src/inputsystem.cpp
    src/virtual_input_component.cpp)

build_internal_lib_component(SOURCES ${_SOURCES})
