set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("HAF Types"
    VERSION 0.9.2.0
    DESCRIPTION "Simple types for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET htypes)

set(sources
    src/types.cpp
)

set(include_dir htypes/include)
set(headers
    ${include_dir}/memory/alloc_func_memmanager.hpp
    ${include_dir}/memory/alloc_func.hpp
    ${include_dir}/memory/allocator.hpp
    ${include_dir}/memory/allocatorfunc.hpp
    ${include_dir}/memory/placement.hpp
    ${include_dir}/properties/basic_property.hpp
    ${include_dir}/properties/iproperty.hpp
    ${include_dir}/properties/properties.hpp
    ${include_dir}/properties/wrapper_property.hpp
    ${include_dir}/algoutils.hpp
    ${include_dir}/array.hpp
    ${include_dir}/basic_dictionary.hpp
    ${include_dir}/basic_str.hpp
    ${include_dir}/cast.hpp
    ${include_dir}/connection.hpp
    ${include_dir}/debug_internal.hpp
    ${include_dir}/dictionary.hpp
    ${include_dir}/function.hpp
    ${include_dir}/growpolicy.hpp
    ${include_dir}/lockablevector.hpp
    ${include_dir}/menum.hpp
    ${include_dir}/object_utils.hpp
    ${include_dir}/object.hpp
    ${include_dir}/p_impl_pointer.hpp
    ${include_dir}/parpar.hpp
    ${include_dir}/rawmemory.hpp
    ${include_dir}/rect.hpp
    ${include_dir}/serializer.hpp
    ${include_dir}/span.hpp
    ${include_dir}/stack.hpp
    ${include_dir}/str_literal.hpp
    ${include_dir}/str_view.hpp
    ${include_dir}/str.hpp
    ${include_dir}/types.hpp
    ${include_dir}/vector_base.hpp
    ${include_dir}/vector_storage.hpp
    ${include_dir}/vector_view.hpp
    ${include_dir}/vector.hpp
    ${include_dir}/vector2d.hpp
)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

#define compile time constants
target_compile_definitions(${CURRENT_TARGET} PRIVATE htypes_EXPORTS)

set(use_pragma_once 1)
if (DEFINED use_pragma_once)
  message("Setting pragma once for htps")
  target_compile_definitions(${CURRENT_TARGET} PUBLIC HTPS_PRAGMA_ONCE=_Pragma\(\"once\"\))
else()
  message("Not Setting pragma once for htps")
  target_compile_definitions(${CURRENT_TARGET} PUBLIC HTPS_PRAGMA_ONCE=)
endif()

# Use Memmamanger
target_compile_definitions(${CURRENT_TARGET} PUBLIC USER_MEM_MANAGER)
target_link_libraries(${CURRENT_TARGET} PUBLIC memmanager)
target_compile_features(${CURRENT_TARGET} INTERFACE cxx_std_20)

addTestingDirectory(tests)
