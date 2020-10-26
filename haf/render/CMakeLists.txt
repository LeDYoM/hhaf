set(_SOURCES 
    i_include/rendersystem.hpp
    i_include/rendertarget.hpp
    src/renderizable.cpp
    src/renderizable_builder.cpp
    src/renderizables.cpp
    src/rendersystem.cpp
    src/rendertarget.cpp
    src/vertexarray.cpp)

build_internal_lib_component(SOURCES ${_SOURCES})
