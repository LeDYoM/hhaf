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

        inline bool containsComponentOfType(const std::type_index &tindex, const vector_shared_pointers<IComponent>&v)
        {
            return (std::find_if(v.cbegin(), v.cend(), [&tindex](const sptr<IComponent> &component) { return tindexOf(component) == tindex; })) != v.cend();
        }

        inline bool containsComponentOfType(const sptr<IComponent> &c, const vector_shared_pointers<IComponent>&v)
        {
            return containsComponentOfType(tindexOf(c),v);
        }
    }

    bool ComponentContainer::addComponent(sptr<IComponent> nc)
    {
        assert_release(nc != nullptr, "Trying to add a nullptr component");
        const auto& tinfo(typeid(*nc));
        const std::type_index tindex(tinfo);
        
        log_debug_info("Adding component of type ", tinfo.name()," wich has an index of ",tindex.hash_code());
        log_debug_info("Searching for another component of the same type...");
        
        sptr<IComponent> component(std::move(nc));
        const bool alreadyInConainer(containsComponentOfType(component, m_components.current()));

        if (!alreadyInConainer)
        {
            log_debug_info("Not found. Adding it");
            component->m_sceneNode = m_sceneNode;
            m_components.push_back(component);
            component->onAttached();
            return true;
        }
        log_debug_info("Component type already present");
        return false;
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
