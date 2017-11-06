#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "scenenode.hpp"
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/components/parentrendercomponent.hpp>

namespace lib::scene
{
	template <typename T>
	class RenderizableSceneNode : public SceneNode
	{
	public:
		RenderizableSceneNode(SceneNode *const parent, str name) : SceneNode{ parent, name } {}

		void create() override {
			m_node = createRenderizable<T>(name()+"_node");
		}

		sptr<T> node() noexcept { return m_node; }
		const sptr<T> node() const noexcept { return m_node; }

	private:
		sptr<T> m_node;
	};

	template <typename RenderizableT>
	class RenderizableSceneNodeComponent : public ParentRenderComponent<RenderizableT>
	{
	private:
		virtual sptr<RenderizableT> getRenderNodeToAttach() override {
			return node();
		}
	};

	using TextSceneNode = RenderizableSceneNode<nodes::NodeText>;
}

#endif
