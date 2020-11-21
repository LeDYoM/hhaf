set (_SOURCES 
    i_include/shareddatasystem.hpp
    src/address.cpp
    src/shareddatasystem.cpp
    src/shareddata.cpp
)

build_internal_lib_component(SOURCES ${_SOURCES})
