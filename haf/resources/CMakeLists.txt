set(_SOURCES
    i_include/bmpfont.hpp
    i_include/bmpfont_private.hpp
    i_include/bmpfontfactory.hpp
    i_include/font_utils.hpp
    i_include/resourcemanager_private.hpp
    i_include/resourcemanager.hpp
    i_include/resources_config_data.hpp
    i_include/shader.hpp
    i_include/texture.hpp
    i_include/ttfont.hpp
    i_include/ttfontinstance.hpp
    src/bmpfont.cpp
    src/bmpfontfactory.cpp
    src/font_utils.cpp
    src/iresourceconfigurator.cpp
    src/iresourceretriever.cpp
    src/resourcemanager.cpp
    src/shader.cpp
    src/texture.cpp
    src/ttfont.cpp
    src/ttfontinstance.cpp
    )

build_internal_lib_component(SOURCES ${_SOURCES})
