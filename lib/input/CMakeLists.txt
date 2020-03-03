project (input CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/input_component_base.cpp"
    "src/inputcomponent.cpp"
    "src/inputdriver.cpp"
    "src/inputsystem.cpp"
    "src/virtual_input_component.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    SOURCES
    ${_SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
