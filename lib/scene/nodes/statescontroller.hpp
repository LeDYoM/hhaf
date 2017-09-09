#pragma once

#ifndef LIB_STATES_CONTROLLER_INCLUDE_HPP__
#define LIB_STATES_CONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scene.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			class StatesController
			{
			public:
				void configure();

				Property<const vector_shared_pointers<scene::SceneNode>*> nodes;
				Property<u32> activeNodeIndex;

				const sptr<scene::SceneNode> &activeNode() const noexcept {
					return (*(nodes()))[activeNodeIndex()];
				}
			private:
				u32 m_lastActiveNodeIndex{};
			};
		}
	}
}

#endif
