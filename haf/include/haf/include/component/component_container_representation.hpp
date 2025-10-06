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

    core::vector<core::sptr<Component>> m_components;
};
}  // namespace haf::component

#endif
