project (backend_dev)
cmake_minimum_required (VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})

set(include_dir ${PROJECT_SOURCE_DIR}/backend_dev/include)
set(headers
    ${include_dir}/camera_data.hpp
    ${include_dir}/factory_types.hpp
    ${include_dir}/ibackendregister.hpp
    ${include_dir}/ibmp_font.hpp
    ${include_dir}/ifactory.hpp
    ${include_dir}/ifont.hpp
    ${include_dir}/iinputdriver.hpp
    ${include_dir}/ikey.hpp
    ${include_dir}/imaterial_data.hpp
    ${include_dir}/iresource_descriptor.hpp
    ${include_dir}/iresource_manager.hpp
    ${include_dir}/iresourcefactories.hpp
    ${include_dir}/iresourcefactory.hpp
    ${include_dir}/iresourceinfo.hpp
    ${include_dir}/itexture.hpp
    ${include_dir}/ittfont.hpp
    ${include_dir}/ivertex.hpp
    ${include_dir}/iwindow.hpp
    ${include_dir}/resource_load_parameters.hpp
)

build_lib_component(HEADERS_ONLY
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    HEADERS ${headers}
)
