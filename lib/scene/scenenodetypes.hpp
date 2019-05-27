#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/components/renderizables.hpp>

#include "scenenode.hpp"

namespace lib::scene
{
	class RenderizableSceneNode : public SceneNode
	{
	public:
		RenderizableSceneNode(SceneNode *const parent, str name) : 
            SceneNode{ parent, name }
        {
                            log_debug_info("A");

            m_node = ensureComponentOfType<Renderizables>()->
                createNode(name + "_node");
        }

		sptr<Renderizable> node() noexcept { return m_node; }
		const sptr<Renderizable> node() const noexcept { return m_node; }

	private:
		sptr<Renderizable> m_node;
	};
}

#endif
