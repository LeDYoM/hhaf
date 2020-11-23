project(bin2array 
    DESCRIPTION "Program to convert binary files to C/C++ array files"
    LANGUAGES CXX)

set(SOURCES main.cpp)

set(CURRENT_TARGET ${PROJECT_NAME})

add_executable(${CURRENT_TARGET} ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)
