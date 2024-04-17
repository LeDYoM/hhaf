set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("fsu"
    VERSION 0.0.1.0
    DESCRIPTION "File System Utils"
    LANGUAGES CXX
)

set(CURRENT_TARGET fsu)

set(include_dir fsu/include)
set(headers
    ${include_dir}/file_system.hpp
    ${include_dir}/fsu.hpp
    ${include_dir}/ifile_driver.hpp
    ${include_dir}/iin_file.hpp
    ${include_dir}/in_file.hpp
    ${include_dir}/out_file.hpp
)

set(sources
    src/driver_normal/file_driver_normal.cpp
    src/driver_normal/file_driver_normal.hpp
    src/driver_normal/in_file_normal.cpp
    src/driver_normal/in_file_normal.hpp

    src/file_factory.cpp
    src/file_factory.hpp
    src/file_system_private.cpp
    src/file_system_private.hpp
    src/file_system.cpp
    src/fsu.cpp
    src/in_file_private.cpp
    src/in_file_private.hpp
    src/in_file.cpp
    src/out_file_private.cpp
    src/out_file_private.hpp
    src/out_file.cpp
)

build_lib_component(STATIC HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
${sources} HEADERS ${headers})

set_pragma_once_or_not(FSU true PUBLIC)

target_compile_features(${CURRENT_TARGET} PRIVATE cxx_std_20)
target_link_libraries(${CURRENT_TARGET} PUBLIC htypes)

addTestingDirectory(tests)
