#ifndef LIB_DRAW_COMPONENT_CONTAINER_INCLUDE_HPP__
#define LIB_DRAW_COMPONENT_CONTAINER_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include "icomponent.hpp"
#include <typeinfo>
#include <typeindex>

namespace lib
{
	namespace draw
	{
		class SceneNode;
		class ComponentContainer
		{
		public:
			ComponentContainer(SceneNode *sceneNode) noexcept;
			~ComponentContainer();

			bool addComponent(sptr<IComponent> nc);
			void updateComponents();

			template <typename T>
			sptr<T> ensureComponentOfType()
			{
				auto component(componentOfType<T>());
				if (!component) {
					auto nc(msptr<T>());
					addComponent(nc);
					return std::move(nc);
				}
				return std::move(component);
			}
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
