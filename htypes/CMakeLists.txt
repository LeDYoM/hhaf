set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("HAF Types"
    VERSION 0.9.2.0
    DESCRIPTION "Simple types for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET htypes)
build_lib_module(${CURRENT_TARGET} STATIC)

target_sources(${CURRENT_TARGET}
PUBLIC
  FILE_SET CXX_MODULES
  FILES
    src/array.cppm
    src/memory/alloc_func_memmanager.cppm
    src/memory/alloc_func.cppm
    src/memory/allocator.cppm
    src/memory/allocatorfunc.cppm
    src/memory/placement.cppm
    src/algoutils.cppm
    src/basic_dictionary.cppm
    src/basic_str.cppm
    src/basic_types.cppm
    src/cast.cppm
    src/dictionary.cppm
    src/function.cppm
    src/growpolicy.cppm
    src/hash_table.cppm
    src/hash.cppm
    src/htypes.cppm
    src/menum.cppm
    src/p_impl_pointer.cppm
    src/pair.cppm
    src/raw_memory.cppm
    src/shared_ptr.cppm
    src/span.cppm
    src/stack.cppm
    src/str_functions.cppm
    src/str_literal.cppm
    src/str_view.cppm
    src/str.cppm
    src/unique_ptr.cppm
    src/vector_base.cppm
    src/vector_storage.cppm
    src/vector.cppm
    src/weak_ptr.cppm
)

#build_lib_component(HEADERS_ONLY HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
#              HEADERS ${headers})

#build_command()

# Use Memmamanger
#target_compile_definitions(${CURRENT_TARGET} INTERFACE USER_MEM_MANAGER)
#target_link_libraries(${CURRENT_TARGET} INTERFACE memmanager)
target_compile_features(${CURRENT_TARGET} INTERFACE cxx_std_23)

addTestingDirectory(tests)
