project (backend_dev)
cmake_minimum_required (VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})

build_lib_interface_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
        backend_dev/include/factory_types.hpp
        backend_dev/include/ibackendregister.hpp
        backend_dev/include/ibmpfont.hpp
        backend_dev/include/ifactory.hpp
        backend_dev/include/ifont.hpp
        backend_dev/include/iinputdriver.hpp
        backend_dev/include/ikey.hpp
        backend_dev/include/iprimitivetype.hpp
        backend_dev/include/irenderdata.hpp
        backend_dev/include/irendertarget.hpp
        backend_dev/include/iresourcefactories.hpp
        backend_dev/include/iresourcefactory.hpp
        backend_dev/include/iresourceinfo.hpp
        backend_dev/include/ishader.hpp
        backend_dev/include/itexture.hpp
        backend_dev/include/ittfont.hpp
        backend_dev/include/ivertex.hpp
        backend_dev/include/iwindow.hpp
)
