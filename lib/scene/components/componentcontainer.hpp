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
			constexpr ComponentContainer(SceneNode *sceneNode = nullptr) noexcept : m_sceneNode{ sceneNode } {}
			inline ~ComponentContainer() = default;

			bool addComponent(sptr<IComponent> nc);

			template <typename T>
			sptr<T> ensureComponentOfType() {
				auto component(componentOfType<T,false>());
				if (!component) {
					auto nc(msptr<T>());
					addComponent(nc);
					return nc;
				}
				return component;
			}

			template <typename T>
			void ensureComponentOfType(sptr<T> &component) {
				component = ensureComponentOfType<T>();
			}

			void updateComponents();

			/**
			* Returns the component of the specified type if exists
			* @param T type of the component to be retrieved
			* @returns A shared pointer to the container or nullptr if not found
			*/
			template <typename T,bool showLog=true>
			sptr<T> componentOfType() const
			{
				sptr<IComponent> cot(componentOfType(std::type_index(typeid(T))));
				if constexpr (showLog)
					assert_debug(cot != nullptr, "Component not found");
				return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
			}

			const sptr<IComponent> componentOfType(const std::type_index& ti) const;
			void clearComponents() noexcept { m_components.clear(); m_sceneNode = nullptr; }
		private:
			SceneNode *m_sceneNode;
			vector_shared_pointers<IComponent> m_components;
		};
	}
}

#endif
