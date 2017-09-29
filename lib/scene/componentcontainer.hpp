#pragma once

#ifndef LIB_SCENE_COMPONENTCONTAINER_INCLUDE_HPP__
#define LIB_SCENE_COMPONENTCONTAINER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
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
			ComponentContainer(SceneNode *sceneNode) noexcept;
			~ComponentContainer();

			bool addComponent(sptr<IComponent> nc);

			template <typename T, typename... Args>
			sptr<T> emplaceComponentOfType(Args&&... args) {
				auto component(componentOfType<T>());
				if (!component) {
					auto nc(msptr<T>(std::forward<Args>(args)...));
					addComponent(nc);
					return nc;
				}
				return component;
			}

			template <typename T>
			sptr<T> ensureComponentOfType()
			{
				return emplaceComponentOfType<T>();
			}

			void updateComponents();

			/**
			* Returns the component of the specified type if exists
			* @param T type of the component to be retrieved
			* @returns A shared pointer to the container or nullptr if not found
			*/
			template <typename T>
			sptr<T> componentOfType()
			{
				sptr<IComponent> cot(componentOfType(std::type_index(typeid(T))));
				return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
			}

			const sptr<IComponent> componentOfType(const std::type_index& ti);
			void clearComponents() noexcept { m_components.clear(); m_sceneNode = nullptr; }
		private:
			SceneNode *m_sceneNode;
			vector_shared_pointers<IComponent> m_components;
		};
	}
}

#endif
