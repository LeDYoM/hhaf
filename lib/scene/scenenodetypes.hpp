#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>

#include "scenenode.hpp"

namespace lib::scene
{
	template <typename T>
	class RenderizableSceneNode : public SceneNode
	{
	public:
		constexpr RenderizableSceneNode(SceneNode *const parent, str name) : 
            SceneNode{ parent, name }, m_node{ SceneNode::createRenderizable<T>(name + "_node") }
        {
        }

		constexpr sptr<T> node() noexcept { return m_node; }
		constexpr const sptr<T> node() const noexcept { return m_node; }

	private:
		const sptr<T> m_node;
	};

    using ShapeSceneNode = RenderizableSceneNode<nodes::NodeShape>;
    using QuadSceneNode = RenderizableSceneNode<nodes::NodeQuad>;
}

#endif
