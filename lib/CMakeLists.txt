project (lib)

set(SOURCE_FILES_LIST
    backend/backendfactory.cpp
    backend/backendfactory.hpp
    backend/interfaces.hpp
    backend/itexturefactory.hpp
    backend/itexture.hpp
    backend/ittfontfactory.hpp
    backend/ittfont.hpp
    backend/iwindow.hpp

    board/boardmodel.cpp
    board/boardmodel.hpp
    board/itilescontroller.hpp

	core/appservice.hpp
	core/compconfig.hpp
	core/debugsystem.cpp
	core/debugsystem.hpp
	core/factory.hpp
	core/file.cpp
	core/file.hpp
	core/host.cpp
	core/host.hpp
	core/hostcontext.cpp
	core/inputsystem.cpp
	core/inputsystem.hpp
	core/main.cpp
	core/memmanager.cpp
	core/memmanager.hpp
	core/randomizer.cpp
	core/randomizer.hpp
	core/resourcemanager.cpp
	core/resourcemanager.hpp
	core/serializer.hpp
	core/window.cpp
	core/window.hpp

	include/classmacros.hpp
	include/core/hostcontext.hpp
	include/iapp.hpp
	include/iresourceloader.hpp
	include/key.hpp
	include/lib.hpp
	include/main.hpp
	include/windowcreationparams.hpp

	scene/color.hpp

	scene/components/animationcomponent.cpp
	scene/components/animationcomponent.hpp
	scene/components/componentcontainer.cpp
	scene/components/componentcontainer.hpp
	scene/components/debugvarscomponent.cpp
	scene/components/debugvarscomponent.hpp
	scene/components/discretetextcomponent.cpp
	scene/components/discretetextcomponent.hpp
	scene/components/elementselector.cpp
	scene/components/elementselector.hpp
	scene/components/icomponent.hpp
	scene/components/inputcomponent.cpp
	scene/components/inputcomponent.hpp
	scene/components/parentrendercomponent.hpp
	scene/components/statescontroller.hpp
	scene/components/texteditorcomponent.cpp
	scene/components/texteditorcomponent.hpp
	scene/components/timercomponent.cpp
	scene/components/timercomponent.hpp

	scene/hasname.hpp
	scene/ianimation.hpp

	scene/nodes/tablenode.hpp
	scene/nodes/textquad.cpp
	scene/nodes/textquad.hpp
	scene/nodes/theme.hpp

	scene/renderdata.hpp
	scene/renderizable.cpp
	scene/renderizable.hpp

	scene/renderizables/isimplenode.cpp
	scene/renderizables/isimplenode.hpp
	scene/renderizables/nodequad.cpp
	scene/renderizables/nodequad.hpp
	scene/renderizables/nodeshape.cpp
	scene/renderizables/nodeshape.hpp
	scene/renderizables/nodetext.cpp
	scene/renderizables/nodetext.hpp

	scene/scene.cpp
	scene/scene.hpp
	scene/scenemanager.cpp
	scene/scenemanager.hpp
	scene/scenenode.cpp
	scene/scenenode.hpp
	scene/scenenodetypes.hpp
	scene/texture.cpp
	scene/texture.hpp
	scene/transformable.cpp
	scene/transformable.hpp
	scene/transformation.cpp
	scene/transformation.hpp
	scene/ttfont.cpp
	scene/ttfont.hpp
	scene/vertex.hpp
	scene/vertexarray.cpp
	scene/vertexarray.hpp
)


include_directories ("..")

set(LIB_VERSION_MAJOR "1")
set(LIB_VERSION_MINOR "5")
set(LIB_VERSION_PATCH "1")

configure_file(config.hpp.in config.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set (CURRENT_TARGET lib)

add_library(${CURRENT_TARGET} STATIC ${SOURCE_FILES_LIST})

target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
