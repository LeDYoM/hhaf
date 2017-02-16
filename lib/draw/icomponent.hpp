#ifndef LIB_DRAW_ICOMPONENT_INCLUDE_HPP__
#define LIB_DRAW_ICOMPONENT_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>

namespace lib
{
	namespace draw
	{
		/**
		* Base class for all components attached to a scene node.
		*/
		class IComponent
		{
		public:
			/**
			* Constructor.
			* Constructs a new IComponent attached to the specified SceneNode
			*/
			constexpr IComponent() {}
			virtual void update() = 0;
			virtual ~IComponent() {}

			inline SceneNode *const attachedNode() const noexcept { return m_sceneNode; }
		private:
			SceneNode *m_sceneNode{};
			friend class ComponentContainer;
		};
	}
}

#endif
