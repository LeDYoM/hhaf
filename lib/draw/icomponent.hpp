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
			virtual void update() = 0;
			virtual ~IComponent() {}
		};

		class IAttachedSceneNodeNodeComponent : public IComponent
		{
		public:
			ReadOnlyRefProperty<SceneNodeSPtr> sceneNode;
		protected:
			SceneNodeSPtr m_sceneNode;
		};

		class ComponentContainer
		{
		public:
			constexpr ComponentContainer()
		};
	}
}

#endif
