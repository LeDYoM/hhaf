project (mtypes)

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file (GLOB _SOURCES "src/*.cpp")
#file (GLOB _HEADERS "*.hpp")
 
file (GLOB _INCLUDES "include/*.hpp")

set (CURRENT_TARGET mtypes) 

add_library(${CURRENT_TARGET} 
	SHARED 
	${_SOURCES} 
	#${_HEADERS} 
	${_INCLUDES}
	)

include(GenerateExportHeader)
generate_export_header( ${CURRENT_TARGET})

install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION .)

set(MTYPES_INCLUDE "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
message("mtypes include directory: " ${MTYPES_INCLUDE})
