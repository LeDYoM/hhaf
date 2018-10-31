enable_testing()

set(UNIT_TEST_LIST
	main
	scene/scenecontroller
	scene/scenemanager
	scene/scenenode
	scene/components/componentcontainer
	scene/components/statescontroller
)

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST ${NAME}.test.cpp)
endforeach()

set(TARGET_NAME lib_utests)
set(CMAKE_CXX_STANDARD 17)

add_executable(${TARGET_NAME}
  ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME} PRIVATE lib)
target_link_libraries(${TARGET_NAME} PRIVATE mtypes)

include_directories(${TARGET_NAME} INTERFACE ${CATCH_INCLUDE_DIR})

# add_test( NAME all COMMAND CTest)
include (Catch)
catch_discover_tests(${TARGET_NAME})
