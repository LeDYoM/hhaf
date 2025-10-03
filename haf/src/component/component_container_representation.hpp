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
    sptr<Component> getComponentFromTypeIndex(
        utils::type_index const& tindex) const;

    void push_back(sptr<Component>&& new_component);

    core::vector<core::sptr<Component>> m_components;
};
}  // namespace haf::component

#endif
