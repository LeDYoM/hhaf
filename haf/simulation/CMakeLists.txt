set (_SOURCES 
    i_include/simulationsystem.hpp
    src/simulationsystem.cpp
    src/simulationsystem_private.hpp
    )

build_internal_lib_component(SOURCES ${_SOURCES})
