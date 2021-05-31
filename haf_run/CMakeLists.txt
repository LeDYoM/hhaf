project(haf_run)

set(sources 
    src/main.cpp
    )

set(CURRENT_TARGET haf_run)

add_executable(${CURRENT_TARGET})
target_sources(${CURRENT_TARGET} PRIVATE ${sources})
target_link_libraries(${CURRENT_TARGET} PRIVATE agloader memmanager)

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)

set_install_options_for_target(${CURRENT_TARGET})
