cmake_minimum_required (VERSION 3.14)
project(boardmanager_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    boardmanager
)

add_haf_test_executable(SOURCE_TESTS ${SOURCE_TESTS})

target_link_libraries(${CURRENT_TARGET} PRIVATE boardmanager)
