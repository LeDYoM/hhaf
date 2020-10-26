set(_SOURCES
    i_include/get_system.hpp
    i_include/get_systemprovider.hpp
    i_include/systembase.hpp
    i_include/systemcontroller.hpp
    i_include/systemdatawrappercreator.hpp
    i_include/systemprovider.hpp
    src/systembase.cpp
    src/get_systemprovider.cpp
    src/get_system.cpp
    src/interfaceaccess.cpp
    src/systemaccess.cpp
    src/systemcontroller.cpp
    src/systemprovider.cpp)

build_internal_lib_component(SOURCES ${_SOURCES})
