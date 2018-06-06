#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/components/parentrendercomponent.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include "scenenode.hpp"

namespace lib::scene
{
	template <typename T>
	class RenderizableSceneNode : public SceneNode
	{
	public:
		RenderizableSceneNode(SceneNode *const parent, str name) : SceneNode{ parent, name } {}

		void onCreated() override {
			m_node = createRenderizable<T>(name()+"_node");
		}

		sptr<T> node() noexcept { return m_node; }
		const sptr<T> node() const noexcept { return m_node; }

	private:
		sptr<T> m_node;
	};

	template <typename RenderizableT, typename BaseComponent>
	class RenderizableSceneNodeComponent : public ParentRenderComponent<RenderizableT, BaseComponent>
	{
	public:
		using BaseClass = ParentRenderComponent<RenderizableT,BaseComponent>;
        using ParentNodeClass = RenderizableSceneNode<RenderizableT>;
		void onAttached() override {
			if (auto parentNode = BaseClass::template attachedNodeAs<ParentNodeClass>()) {
				m_renderizableNode = parentNode->node();
			}
			BaseClass::onAttached();
		}
	private:
		sptr<RenderizableT> getRenderNodeToAttach() override {
			return m_renderizableNode;
		}

		sptr<RenderizableT> m_renderizableNode;
	};

	using TextSceneNode = RenderizableSceneNode<nodes::NodeText>;
    using ShapeSceneNode = RenderizableSceneNode<nodes::NodeShape>;
}

#endif
