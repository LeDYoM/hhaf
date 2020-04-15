project(host)
cmake_minimum_required(VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})

set(SRC_FILES "src/apploader.cpp" "src/host.cpp" "src/main.cpp")

build_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${SRC_FILES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)