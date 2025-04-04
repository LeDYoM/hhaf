cmake_minimum_required(VERSION 3.12)

project(default_menu_paged
    VERSION 0.1.0.0
    LANGUAGES CXX
    )

set (CURRENT_TARGET ${PROJECT_NAME})

set(SRC_FILES

    default_menu_paged/include/menu_finished_status.hpp
    default_menu_paged/include/menu_page.hpp
    default_menu_paged/include/menu_paged_black_board.hpp
    default_menu_paged/include/menu_paged_input_component.hpp
    default_menu_paged/include/menu_paged_option.hpp
    default_menu_paged/include/menu_paged.hpp
    default_menu_paged/include/page_options.hpp
    default_menu_paged/include/range_option.hpp

    src/menu_page.cpp
    src/menu_paged_input_component.cpp
    src/menu_paged_option.cpp
    src/menu_paged.cpp
    src/range_option.cpp
)

build_lib_ext(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${SRC_FILES}
)
