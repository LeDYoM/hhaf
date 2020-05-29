project(librun)

set(SOURCES main.cpp)

set(CURRENT_TARGET librun)

add_executable(${CURRENT_TARGET} ${SOURCES})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)

install(TARGETS ${CURRENT_TARGET} DESTINATION .)
