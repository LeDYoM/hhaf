enable_testing()

set(UNIT_TEST_LIST
    str
    dicty
    parpar)

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST ${NAME}.test.cpp)
endforeach()

set(TARGET_NAME mtypes_tests)
set(CMAKE_CXX_STANDARD 17)

add_executable(${TARGET_NAME}
  ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME}
  PRIVATE mtypes)

include_directories(${TARGET_NAME}
  INTERFACE ${CATCH_INCLUDE_DIR})

add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit)
