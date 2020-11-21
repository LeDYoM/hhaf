project(haf_run)

set(SOURCES main.cpp)

set(CURRENT_TARGET haf_run)

add_executable(${CURRENT_TARGET} ${SOURCES})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE memmanager)

add_development_dependency(${CURRENT_TARGET} host)
find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)

install(TARGETS ${CURRENT_TARGET} DESTINATION .)
