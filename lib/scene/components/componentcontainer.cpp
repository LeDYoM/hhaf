#include "componentcontainer.hpp"

#include <lib/include/liblog.hpp>

#include <algorithm>

namespace lib::scene
{
    namespace
    {
        inline std::type_index tindexOf(const sptr<IComponent> &c)
        {
            return std::type_index(typeid(*c));
        }

        inline sptr<IComponent> getComponentFromTypeIndex(const std::type_index &tindex, const vector_shared_pointers<IComponent>&v)
        {
            auto iterator (std::find_if(v.cbegin(), v.cend(), [&tindex](const sptr<IComponent> &component) { return tindexOf(component) == tindex; }));
            return (iterator == v.cend()) ? nullptr : (*iterator);
        }
    }

    ComponentContainer::~ComponentContainer() = default;

    bool ComponentContainer::addComponent(sptr<IComponent> nc)
    {
        log_assert(nc != nullptr, "Trying to add a nullptr component");

        nc->m_sceneNode = m_sceneNode;
        m_components.push_back(nc);
        nc->onAttached();
        return true;
    }

    void ComponentContainer::updateComponents() 
    {
        m_components.update();

        if (!m_components.current().empty()) 
        {
            for (auto component : m_components.current())
            {
                component->update();
            }
            m_components.update();
        }
    }

    void ComponentContainer::postUpdateComponents()
    {
        m_components.update();

        if (!m_components.current().empty()) 
        {
            for (auto component : m_components.current())
            {
                component->postUpdate();
            }
            m_components.update();
        }
    }

    const sptr<IComponent> ComponentContainer::componentOfType(const std::type_index & ti) const
    {
        return getComponentFromTypeIndex(ti, m_components.next());
    }
}
