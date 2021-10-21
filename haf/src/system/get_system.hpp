#ifndef HAF_SYSTEM_INTERNAL_GET_INCLUDE_HPP
#define HAF_SYSTEM_INTERNAL_GET_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::sys
{
class SystemAccess;

template <typename SystemType>
SystemType const& getSystem(types::rptr<SystemAccess const>);

template <typename SystemType>
SystemType& getSystem(types::rptr<SystemAccess>);

template <typename SystemType>
SystemType const& getSystem(types::rptr<scene::SceneNode const>);

template <typename SystemType>
SystemType& getSystem(types::rptr<scene::SceneNode>);
}  // namespace haf::sys

#endif
