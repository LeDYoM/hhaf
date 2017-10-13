#pragma once

#ifndef LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__
#define LIB_SCENE_SCENENODETYPES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "scenenode.hpp"
#include <lib/scene/renderizables/nodetext.hpp>

namespace lib
{
	namespace scene
	{
		template <typename T>
		class RenderizableSceneNode : public SceneNode
		{
		public:

			void create() override {
				createRenderizable<T>(name()+"_node");
			}

			sptr<T> operator()() noexcept { return m_node; }
			const sptr<T> operator()() const noexcept { return m_node; }

		private:
			sptr<T> m_node;
		};

		using TextSceneNode = RenderizableSceneNode<nodes::NodeText>;
	}
}

#endif
