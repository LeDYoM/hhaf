project (loader)

file (GLOB _SOURCES "*.cpp")
file (GLOB _HEADERS "*.hpp")
 
file (GLOB _INCLUDES "include/*.hpp")

set (CURRENT_TARGET loader) 

add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS} ${_INCLUDES})
target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${CURRENT_TARGET} ${CMAKE_DL_LIBS})

install (TARGETS ${CURRENT_TARGET} 
	LIBRARY DESTINATION .
	RUNTIME DESTINATION .
)

