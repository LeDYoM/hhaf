project(haf_integrated_backend)

file(GLOB SOURCES "*.cpp" "*.hpp")

set(CURRENT_TARGET haf_integrated_backend)

include (backend_client_functions)

build_concrete_backend(
    SOURCES
    ${SOURCES}
)
