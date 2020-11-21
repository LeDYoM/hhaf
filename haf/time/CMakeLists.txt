set (_SOURCES 
    i_include/timesystem.hpp
    src/timer.cpp
    src/timercomponent.cpp
    src/timepoint.cpp
    src/timesystem.cpp
    src/timeview.cpp
)

build_internal_lib_component(SOURCES ${_SOURCES})
