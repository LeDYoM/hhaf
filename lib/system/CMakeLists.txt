project (system CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "filesystem.cpp"
    "inputsystem.cpp"
    "randomsystem.cpp"
    "scenemanager.cpp"
    "systemprovider.cpp"
    "timesystem.cpp"
    "window.cpp"
)

set (_HEADERS
    "appservice.hpp"
    "filesystem.hpp"
    "inputsystem.hpp"
    "isystemprovider.hpp"
    "randomsystem.hpp"
    "scenemanager.hpp"
    "systemprovider.hpp"
    "timesystem.hpp"
    "window.hpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

add_library(${CURRENT_TARGET} STATIC ${_SOURCES} ${_HEADERS})
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE render)
target_link_libraries(${CURRENT_TARGET} PRIVATE simulation)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PRIVATE resources)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)

target_include_directories(${CURRENT_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
