project (system CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "filesystem.cpp"
    "inputsystem.cpp"
    "randomsystem.cpp"
    "rendersystem.cpp"
    "rendertarget.cpp"
    "resourcemanager.cpp"
    "simulationsystem.cpp"
    "systemprovider.cpp"
    "timesystem.cpp"
    "window.cpp"
)

set (_HEADERS
    "appservice.hpp"
    "filesystem.hpp"
    "inputsimulation.hpp"
    "inputsystem.hpp"
    "randomsystem.hpp"
    "rendersystem.hpp"
    "rendertarget.hpp"
    "resourcemanager.hpp"
    "simulationaction.hpp"
    "simulationactiongroup.hpp"
    "simulationsystem_private.hpp"
    "simulationsystem.hpp"
    "systemprovider.hpp"
    "timesystem.hpp"
    "window.hpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

add_library(${CURRENT_TARGET} STATIC ${_SOURCES} ${_HEADERS})
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)

target_include_directories(${CURRENT_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
