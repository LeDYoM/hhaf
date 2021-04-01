set (_SOURCES 
    src/renderizable_scenenode.cpp
    src/scenenodetext.cpp
    src/tablenode_imp.cpp
    src/text_table_node.cpp
    src/textquad.cpp
)

build_internal_lib_component(SOURCES ${_SOURCES})
