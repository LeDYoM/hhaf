project(menu_paged)
cmake_minimum_required(VERSION 3.12)

set (CURRENT_TARGET ${PROJECT_NAME})

set(SRC_FILES 
    "src/menu_page.cpp"
    "src/menu_paged.cpp"
    "src/menu_paged_option.cpp"
    "src/menu_paged_input_component.cpp")

build_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${SRC_FILES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
