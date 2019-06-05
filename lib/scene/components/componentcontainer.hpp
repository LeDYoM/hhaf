#pragma once

#ifndef LIB_SCENE_COMPONENTCONTAINER_INCLUDE_HPP
#define LIB_SCENE_COMPONENTCONTAINER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/lockablevector.hpp>
#include "icomponent.hpp"
#include <typeinfo>
#include <typeindex>

namespace lib
{
	namespace scene
	{
		class SceneNode;
		class ComponentContainer
		{
		public:
			constexpr ComponentContainer(SceneNode *sceneNode = nullptr) noexcept : m_sceneNode{ sceneNode } {}
			inline ~ComponentContainer() = default;

			bool addComponent(sptr<IComponent> nc);

			template <typename T>
			sptr<T> ensureComponentOfType()
            {
				auto component(componentOfType<T>());
				if (!component)
                {
					auto nc(msptr<T>());
					addComponent(nc);
					return nc;
				}
				return component;
			}

			template <typename T>
			void ensureComponentOfType(sptr<T> &component)
            {
				component = ensureComponentOfType<T>();
			}

			void updateComponents();
            void postUpdateComponents();

			/**
			* Returns the component of the specified type if exists
			* @param T type of the component to be retrieved
			* @return A shared pointer to the container or nullptr if not found
			*/
			template <typename T>
			sptr<T> componentOfType() const
			{
				sptr<IComponent> cot(componentOfType(std::type_index(typeid(T))));
				return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
			}

			void clearComponents() noexcept { m_components.clear(); m_sceneNode = nullptr; }
		private:
			const sptr<IComponent> componentOfType(const std::type_index& ti) const;

			SceneNode *m_sceneNode;
			LockableVector<sptr<IComponent>> m_components;
		};
	}
}

#endif
