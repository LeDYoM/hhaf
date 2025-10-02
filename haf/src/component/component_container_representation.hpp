HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_REPRESENTATION_INCLUDE_HPP

#include "haf_private.hpp"

namespace haf::component
{
/// @brief
class HAF_PRIVATE ComponentContainerRepresentation
{
    vector<sptr<Component>> m_components;
}
}  // namespace haf::component

#endif
