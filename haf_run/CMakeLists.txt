project(haf_run)

set(SOURCES main.cpp)

set(CURRENT_TARGET haf_run)

add_executable(${CURRENT_TARGET} ${SOURCES})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE memmanager)

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)
