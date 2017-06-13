project (binterface)

set (INCLUDE_DIR "ibackend/include/")
file (GLOB _SOURCES "${INCLUDE_DIR}*.hpp")
set (CURRENT_TARGET binterface)

add_library(${CURRENT_TARGET} INTERFACE)
target_sources(${CURRENT_TARGET} INTERFACE ${_SOURCES})

target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})
install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION .)
