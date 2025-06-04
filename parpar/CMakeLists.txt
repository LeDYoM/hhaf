set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("PARameter PARser"
    VERSION 1.0.0.1
    DESCRIPTION "Parameter Parser"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES C CXX
)

set(CURRENT_TARGET parpar)

set(include_dir parpar/include)
set(headers
    ${include_dir}/parpar.hpp
)

build_lib_component(HEADERS_ONLY HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
              HEADERS ${headers})

set_pragma_once_or_not(PARPAR true INTERFACE)
target_compile_features(${CURRENT_TARGET} INTERFACE cxx_std_23)
target_link_libraries(${CURRENT_TARGET} INTERFACE htypes)
addTestingDirectory(tests)
