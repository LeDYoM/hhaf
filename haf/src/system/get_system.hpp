#ifndef HAF_SYSTEM_INTERNAL_GET_INCLUDE_HPP
#define HAF_SYSTEM_INTERNAL_GET_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::sys
{
class SystemAccess;

template <typename SystemType>
const SystemType& getSystem(htps::rptr<const SystemAccess>);

template <typename SystemType>
SystemType& getSystem(htps::rptr<SystemAccess>);

template <typename SystemType>
const SystemType& getSystem(htps::rptr<const scene::SceneNode>);

template <typename SystemType>
SystemType& getSystem(htps::rptr<scene::SceneNode>);
}  // namespace haf::sys

#endif
