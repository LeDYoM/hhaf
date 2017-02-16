#include "componentcontainer.hpp"

namespace lib
{
	namespace draw
	{
		ComponentContainer::ComponentContainer(SceneNode *sceneNode) 
			: m_sceneNode{ sceneNode } {}

		ComponentContainer::~ComponentContainer() 
		{ 
			m_sceneNode = nullptr; 
			m_components.clear();
		}

		void ComponentContainer::addComponent(uptr<IComponent> nc)
		{
			nc->m_sceneNode = m_sceneNode;
			m_components.push_back(std::move(nc));
		}

		void ComponentContainer::update()
		{
			for (auto &component : m_components) {
				component->update();
			}
		}
	}
}
