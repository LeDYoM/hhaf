HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>
#include <haf/include/utils/type_data.hpp>

namespace haf::component
{
class Component;

class HAF_PRIVATE ComponentContainerRepresentation
{
    core::sptr<Component> getComponentFromTypeIndex(
        utils::type_index const& tindex) const;

    template <typename T>
    core::sptr<T> getComponent() const
    {
        return getComponentFromTypeIndex(utils::type_of<T>());
    }

    template <typename T>
    core::sptr<T> getComponent(sptr<T> c) const
    {
        return getComponentFromTypeIndex(utils::type_of<T>());
    }

    void push_back(core::sptr<Component>&& new_component);

    core::vector<core::sptr<Component>> m_components;
};
}  // namespace haf::component

#endif
