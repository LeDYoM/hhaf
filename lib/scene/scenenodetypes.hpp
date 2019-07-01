#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
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

            m_node = addComponentOfType<Renderizables>()->
                createNode(name + "_node");
        }

        sptr<Renderizable> node() noexcept { return m_node; }
        const sptr<Renderizable> node() const noexcept { return m_node; }

    private:
        sptr<Renderizable> m_node;
    };
}

#endif
