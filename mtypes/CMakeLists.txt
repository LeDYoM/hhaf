project (mtypes)

file (GLOB _SOURCES "src/*.cpp")
file (GLOB _HEADERS "*.hpp")
 
file (GLOB _INCLUDES "mtypes/include/*.hpp")

set (CURRENT_TARGET mtypes) 

add_library(${CURRENT_TARGET} 
	SHARED 
	${_SOURCES}
	${_HEADERS} 
	${_INCLUDES}
	)

install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION .)
target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR})
