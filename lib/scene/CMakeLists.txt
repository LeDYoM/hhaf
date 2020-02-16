project (scene CXX)
cmake_minimum_required(VERSION 3.12)

file (GLOB _SOURCES "*.cpp" "components/*.cpp" "nodes/*.cpp")
file (GLOB _HEADERS "*.hpp" "components/*.hpp" "nodes/*.cpp")

set (CURRENT_TARGET  ${PROJECT_NAME})

add_library(${CURRENT_TARGET} STATIC ${_SOURCES} ${_HEADERS})
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
