set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("Mini C serializer"
    VERSION 0.0.1.0
    DESCRIPTION "Modern C++ serialization"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET mc_serial)

set(include_dir mc_serial/include)
set(headers
    ${include_dir}/interfaces/ideserializable.hpp
    ${include_dir}/interfaces/ifullserializable.hpp
    ${include_dir}/interfaces/iserializable.hpp
    ${include_dir}/object_parser.hpp
    ${include_dir}/object.hpp
    ${include_dir}/serializer.hpp
    ${include_dir}/text_serializer.hpp
)

build_lib_component(HEADERS_ONLY HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
              HEADERS ${headers})

set_pragma_once_or_not(MCS true INTERFACE)

target_compile_features(${CURRENT_TARGET} INTERFACE cxx_std_23)

addTestingDirectory(tests)
