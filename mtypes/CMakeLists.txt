project (mtypes)

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file (GLOB _SOURCES "src/*.cpp")
file (GLOB _HEADERS "*.hpp")
 
file (GLOB _INCLUDES "mtypes/include/*.hpp")

set (CURRENT_TARGET mtypes) 

message("A ${_SOURCES}")
message("B ${_HEADERS}")
message("C ${_INCLUDES}")
add_library(${CURRENT_TARGET} 
	SHARED 
	${_SOURCES}
	${_HEADERS} 
	${_INCLUDES}
	)

include(GenerateExportHeader)
generate_export_header(${CURRENT_TARGET})
include_directories(${PROJECT_BINARY_DIR})

install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION .)
target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

