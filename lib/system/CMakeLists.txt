project (system CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "systemprovider.cpp"
)

set (_HEADERS
    "appservice.hpp"
    "isystemprovider.hpp"
    "systemprovider.hpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

add_library(${CURRENT_TARGET} STATIC ${_SOURCES} ${_HEADERS})
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)

target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE filesystem)
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE input)
target_link_libraries(${CURRENT_TARGET} PRIVATE random)
target_link_libraries(${CURRENT_TARGET} PRIVATE render)
target_link_libraries(${CURRENT_TARGET} PRIVATE resources)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE shareddata)
target_link_libraries(${CURRENT_TARGET} PRIVATE simulation)
target_link_libraries(${CURRENT_TARGET} PRIVATE time)
target_link_libraries(${CURRENT_TARGET} PRIVATE window)
