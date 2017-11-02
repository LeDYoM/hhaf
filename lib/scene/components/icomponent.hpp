#pragma once

#ifndef LIB_SCENE_ICOMPONENT_INCLUDE_HPP__
#define LIB_SCENE_ICOMPONENT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/log.hpp>

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

			/**
			* Shortcut method to cast to another scenenode type
			*/
			template <typename T>
			inline T*const attachedNodeAs() const { return dynamic_cast<T*>(m_sceneNode); }

			inline const SceneNode *const attachedNode() const noexcept { return m_sceneNode; }
			inline SceneNode *const attachedNode() noexcept { return m_sceneNode; }

			template <typename T, typename... Args>
			sptr<T> ensureSiblingComponentOfType(Args&&... args) {
				assert_release(m_sceneNode != nullptr, "You need to have a node attached before calling this method");
				return m_sceneNode->ensureComponentOfType<T>(std::forward<Args>(args)...);
			}
		private:
			SceneNode *m_sceneNode;
			friend class ComponentContainer;
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
