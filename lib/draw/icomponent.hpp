#ifndef LIB_DRAW_ICOMPONENT_INCLUDE_HPP__
#define LIB_DRAW_ICOMPONENT_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>

namespace lib
{
	namespace draw
	{
		class SceneNode;
		/**
		* Base class for all components attached to a scene node.
		*/
		class IComponent
		{
		public:
			/**
			* Interface to be implemented to update the component
			*/
			virtual void update() = 0;

			/**
			* Destructor
			*/
			virtual ~IComponent() = default;

			inline SceneNode *const attachedNode() const noexcept { return m_sceneNode; }
		private:
			SceneNode *m_sceneNode{};
			friend class ComponentContainer;
		};

		class DataOnlyComponent : public IComponent
		{
			virtual void update() override final {}
		};
	}
}

#endif
