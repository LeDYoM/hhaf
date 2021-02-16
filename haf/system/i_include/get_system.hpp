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
const SystemType& getSystem(mtps::rptr<const SystemAccess>);

template <typename SystemType>
SystemType& getSystem(mtps::rptr<SystemAccess>);

template <typename SystemType>
const SystemType& getSystem(mtps::rptr<const scene::SceneNode>);

template <typename SystemType>
SystemType& getSystem(mtps::rptr<scene::SceneNode>);
}  // namespace haf::sys

#endif
