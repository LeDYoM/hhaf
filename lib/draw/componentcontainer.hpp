#ifndef LIB_DRAW_COMPONENT_CONTAINER_INCLUDE_HPP__
#define LIB_DRAW_COMPONENT_CONTAINER_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include "icomponent.hpp"

namespace lib
{
	namespace draw
	{
		class SceneNode;
		class ComponentContainer final
		{
		public:
			ComponentContainer(SceneNode *sceneNode);
			~ComponentContainer();

			void addComponent(uptr<IComponent> nc);
			void update();
		private:
			SceneNode *m_sceneNode;
			vector_unique_pointers<IComponent> m_components;
		};
	}
}

#endif
