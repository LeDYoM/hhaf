project (mtypes)

set (CURRENT_TARGET mtypes)

file (GLOB _SOURCES "src/*.cpp")
file (GLOB _HEADERS "*.hpp")

file (GLOB _INCLUDES "${CURRENT_TARGET}/include/*.hpp")

add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS} ${_INCLUDES})

target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR})


install (TARGETS ${CURRENT_TARGET}
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)

add_subdirectory(tests)
