project (backend_dev)
cmake_minimum_required (VERSION 3.28)

set (CURRENT_TARGET ${PROJECT_NAME})

set(sources
    src/backend_dev.cppm
    src/factory_types.cppm
    src/ibackend_register.cppm
    src/ibmp_font.cppm
    src/ifactory.cppm
    src/ifont.cppm
    src/iinputdriver.cppm
    src/ikey.cppm
    src/imaterial_data.cppm
    src/iresource_descriptor.cppm
    src/iresource_manager.cppm
    src/iresource_factories.cppm
    src/iresource_factory.cppm
    src/iresource_info.cppm
    src/ishader.cppm
    src/itexture.cppm
    src/ittfont.cppm
    src/ivertex.cppm
    src/iwindow.cppm
    src/resource_load_parameters.cppm
)

build_lib_module(${CURRENT_TARGET} STATIC SOURCES "${sources}")
target_link_libraries(${CURRENT_TARGET} PRIVATE htypes facil_math)
