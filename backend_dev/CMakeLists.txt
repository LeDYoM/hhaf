project (backend_dev)
cmake_minimum_required (VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})

set(include_dir ${PROJECT_SOURCE_DIR}/backend_dev/include)
set(headers
    ${include_dir}/factory_types.hpp
    ${include_dir}/ibackendregister.hpp
    ${include_dir}/ifactory.hpp
    ${include_dir}/ikey.hpp
    ${include_dir}/iwindow_messages_receiver.hpp
    ${include_dir}/iwindow.hpp
)

build_lib_component(HEADERS_ONLY
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    HEADERS ${headers}
)

target_link_libraries(${CURRENT_TARGET} INTERFACE facil_math)
