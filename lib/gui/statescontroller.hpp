#ifndef __LIB_STATES_CONTROLLER_INCLUDE_HPP__
#define __LIB_STATES_CONTROLLER_INCLUDE_HPP__

#pragma once

#include <vector>
#include <mtypes/include/types.hpp>
#include <lib/scene/scene.hpp>

namespace lib
{
	namespace gui
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

#endif
