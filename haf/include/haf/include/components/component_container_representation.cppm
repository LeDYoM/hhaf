module;

#include <haf/include/haf_export.hpp>

module haf:components:component_container_representation;

import :core;
import :utils:type_data;

namespace haf::component
{
class Component;

class HAF_API ComponentContainerRepresentation
{
protected:
    core::sptr<Component> getComponentFromTypeIndex(
        utils::type_index const& tindex) const
    {
        auto iterator(m_components.find_if(
            m_components.cbegin(), m_components.cend(),
            [&tindex](sptr<Component> const& component) {
                return !component.empty()
                    ? utils::type_index(typeid(*component)) == tindex
                    : false;
            }));
        return (iterator == m_components.cend()) ? nullptr : (*iterator);
    }

    template <typename T>
    core::sptr<T> getComponent() const
    {
        return getComponentFromTypeIndex(utils::type_of<T>());
    }

    template <typename T>
    bool getComponent(core::sptr<T>& c) const
    {
        if (c == nullptr)
        {
            auto comp{getComponentFromTypeIndex(utils::type_of<T>())};
            if (comp != nullptr)
            {
                c = core::move(comp);
                return true;
            }
        }
        return false;
    }

    void push_back(sptr<Component>&& new_component)
    {
        m_components.push_back(core::move(new_component));
    }

    void push_back(sptr<Component> const& new_component)
    {
        m_components.push_back(new_component);
    }

    void set_at_index(core::u32 const index,
                      core::sptr<Component>&& new_component)
    {
        m_components.set_at_index(index, core::move(new_component));
    }

    void set_at_index(core::u32 const index,
                      core::sptr<Component> const& new_component)
    {
        m_components.set_at_index(index, new_component);
    }

    decltype(m_components.size()) size() const noexcept
    {
        return m_components.size();
    }

    void resize(core::u32 const newSize) { m_components.resize(newSize); }

    void clear() { m_components.clear(); }

    template <typename Self>
    decltype(auto) operator[](this Self&& self, core::u32 const index)
    {
        return self.m_components[index];
    }

    core::vector<core::sptr<Component>>& components() noexcept
    {
        return m_components;
    }

    core::vector<core::sptr<Component>> const& components() const noexcept
    {
        return m_components;
    }

private:
    core::vector<core::sptr<Component>> m_components;
};
}  // namespace haf::component
