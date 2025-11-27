set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("HAF Types"
    VERSION 0.9.2.0
    DESCRIPTION "Simple types for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET htypes)
build_lib_module(${CURRENT_TARGET})

set(include_dir htypes/include)
set(headers
    ${include_dir}/memory/alloc_func_memmanager.hpp
    ${include_dir}/memory/alloc_func.hpp
    ${include_dir}/memory/allocator.hpp
    ${include_dir}/memory/allocatorfunc.hpp
    ${include_dir}/memory/placement.hpp
    ${include_dir}/algoutils.hpp
    ${include_dir}/array.hpp
    ${include_dir}/basic_dictionary.hpp
    ${include_dir}/basic_str.hpp
    ${include_dir}/cast.hpp
    ${include_dir}/debug_internal.hpp
    ${include_dir}/dictionary.hpp
    ${include_dir}/function.hpp
    ${include_dir}/growpolicy.hpp
    ${include_dir}/lockable_vector.hpp
    ${include_dir}/hash.hpp
    ${include_dir}/menum.hpp
    ${include_dir}/p_impl_pointer.hpp
    ${include_dir}/pair.hpp
    ${include_dir}/rawmemory.hpp
    ${include_dir}/span.hpp
    ${include_dir}/stack.hpp
    ${include_dir}/str_literal.hpp
    ${include_dir}/str_view.hpp
    ${include_dir}/str.hpp
    ${include_dir}/types.hpp
    ${include_dir}/vector_base.hpp
    ${include_dir}/vector_storage.hpp
    ${include_dir}/vector.hpp
)

target_sources(${CURRENT_TARGET}
PUBLIC
  FILE_SET CXX_MODULES
  FILES
    src/memory/alloc_func_memmanager.cppm
    src/memory/alloc_func.cppm
    src/memory/allocator.cppm
    src/memory/allocatorfunc.cppm
    src/memory/placement.cppm
    src/algoutils.cppm
    src/array.cppm
    src/basic_dictionary.cppm
    src/basic_str.cppm
    src/basic_types.cppm
    src/cast.cppm
    src/dictionary.cppm
    src/function.cppm
    src/growpolicy.cppm
    src/lockable_vector.cppm
    src/hash.cppm
    src/htypes.cppm
    src/menum.cppm
    src/p_impl_pointer.cppm
    src/pair.cppm
    src/pair.cppm
    src/rawmemory.cppm
    src/span.cppm
    src/stack.cppm
    src/str_literal.cppm
    src/str_view.cppm
    src/str.cppm
    src/types.cppm
    src/vector_base.cppm
    src/vector_storage.cppm
    src/vector.cppm
)

#build_lib_component(HEADERS_ONLY HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
#              HEADERS ${headers})

#build_command()

set_pragma_once_or_not(HTPS true INTERFACE)

# Use Memmamanger
target_compile_definitions(${CURRENT_TARGET} INTERFACE USER_MEM_MANAGER)
target_link_libraries(${CURRENT_TARGET} INTERFACE memmanager)
target_compile_features(${CURRENT_TARGET} INTERFACE cxx_std_23)

addTestingDirectory(tests)
