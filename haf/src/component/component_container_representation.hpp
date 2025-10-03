HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>

namespace haf::component
{
    class Component;
/// @brief
class HAF_PRIVATE ComponentContainerRepresentation
{
    core::vector<core::sptr<Component>> m_components;
};
}  // namespace haf::component

#endif
