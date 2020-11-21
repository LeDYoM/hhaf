set(_SOURCES 
    i_include/filesystem.hpp
    src/fileserializer.cpp
    src/filesystem.cpp)

build_internal_lib_component(SOURCES ${_SOURCES})
