set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("Mini C serializer"
    VERSION 0.0.1.0
    DESCRIPTION "Modern C++ serialization"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

set(CURRENT_TARGET mc_serial)

set(sources
    src/interfaces/ideserializable.cppm
    src/interfaces/ifullserializable.cppm
    src/interfaces/iserializable.cppm
    src/mc_serial.cppm
    src/object_parser.cppm
    src/object.cppm
    src/serializer.cppm
    src/text_serializer.cppm
)

build_lib_module(${CURRENT_TARGET} EXPORT_ALL SOURCES "${sources}")
target_link_libraries(${CURRENT_TARGET} PRIVATE htypes)
addTestingDirectory(tests)
