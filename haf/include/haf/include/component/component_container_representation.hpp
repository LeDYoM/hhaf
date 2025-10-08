HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/utils/type_data.hpp>

namespace haf::component
{
class Component;

class HAF_API ComponentContainerRepresentation
{
protected:
    core::sptr<Component> getComponentFromTypeIndex(
        utils::type_index const& tindex) const;

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

    void push_back(core::sptr<Component>&& new_component);
    void push_back(core::sptr<Component> const& new_component);
    void set_at_index(core::u32 const index,
                      core::sptr<Component>&& new_component);
    void set_at_index(core::u32 const index,
                      core::sptr<Component> const& new_component);

    auto size() const noexcept { return m_components.size(); }

    void resize(core::u32 const newSize);
    void clear();

    template <typename Self>
    auto operator[](this Self&& self, core::u32 const index) -> decltype(auto)
    {
        return self.m_components[index];
    }

    core::vector<core::sptr<Component>>& components() noexcept;
    core::vector<core::sptr<Component>> const& components() const noexcept;

private:
    core::vector<core::sptr<Component>> m_components;
};
}  // namespace haf::component

#endif
