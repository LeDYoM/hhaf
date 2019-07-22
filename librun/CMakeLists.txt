project(librun)

set(SOURCES main.cpp)

set(CURRENT_TARGET librun)

add_executable(${CURRENT_TARGET} ${SOURCES})
target_link_libraries(${CURRENT_TARGET} PRIVATE host)

install(TARGETS ${CURRENT_TARGET} DESTINATION .)
install(DIRECTORY ${SFML_ROOT}/bin/$<CONFIGURATION>/ DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/zoper/data/ DESTINATION .)

add_subdirectory(tests)
