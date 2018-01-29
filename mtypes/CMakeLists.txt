project (mtypes)

set (CURRENT_TARGET mtypes)

file (GLOB _SOURCES "src/*.cpp")
file (GLOB _HEADERS "*.hpp")

file (GLOB _INCLUDES "${CURRENT_TARGET}/include/*.hpp")

add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS} ${_INCLUDES})

target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR})

#IDE
file (GLOB_RECURSE LIB_HEADERS "*.hpp")
file (GLOB_RECURSE LIB_SOURCES "*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LIB_HEADERS} ${LIB_SOURCES})

install (TARGETS ${CURRENT_TARGET}
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)

add_subdirectory(tests)
