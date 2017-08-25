#ifndef LIB_DRAW_ICOMPONENT_INCLUDE_HPP__
#define LIB_DRAW_ICOMPONENT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

namespace lib
{
	namespace scene
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

			/**
			* Method called after the component is attached to a node.
			* Override it to perform initialization
			*/
			virtual void onAttached() {}

			inline SceneNode *const attachedNode() const noexcept { return m_sceneNode; }
			
			/**
			* Shortcut method to cast to another scenenode type
			*/
			template <typename T>
			inline T*const attachedNodeAs() const { return m_sceneNode->snCast<T>(); }
		private:
			SceneNode *m_sceneNode;
			friend class ComponentContainer;
		};

		class DataOnlyComponent : public IComponent
		{
			virtual void update() override final {}
		};

		template <typename T1, typename T2>
		class IComponentMixin : public IComponent
		{
			virtual void update() override
			{
				T1::update();
				T2::update();
			}
		};
	}
}

#endif
