#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/components/parentrendercomponent.hpp>
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

	template <typename Renderizable_t, typename BaseComponent>
	class RenderizableSceneNodeComponent : public ParentRenderComponent<Renderizable_t, BaseComponent>
	{
	public:
		using BaseClass = ParentRenderComponent<Renderizable_t,BaseComponent>;
        using ParentNodeClass = RenderizableSceneNode<Renderizable_t>;
		void onAttached() override {
			if (auto parentNode = BaseClass::template attachedNodeAs<ParentNodeClass>()) {
				m_renderizableNode = parentNode->node();
			}
			BaseClass::onAttached();
		}
	private:
		sptr<Renderizable_t> getRenderNodeToAttach() override {
			return m_renderizableNode;
		}

		sptr<Renderizable_t> m_renderizableNode;
	};

    using ShapeSceneNode = RenderizableSceneNode<nodes::NodeShape>;
    using QuadSceneNode = RenderizableSceneNode<nodes::NodeQuad>;
}

#endif
