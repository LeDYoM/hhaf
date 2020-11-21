set (_SOURCES 
    i_include/window.hpp
    src/window.cpp
    src/window_properties.cpp
    )

build_internal_lib_component(SOURCES ${_SOURCES})
