HAF_PRAGMA_ONCE
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
class ISystemProvider;

template <typename SystemType>
[[nodiscard]] SystemType const& getSystem(htps::rptr<SystemAccess const>);

template <typename SystemType>
[[nodiscard]]SystemType& getSystem(htps::rptr<SystemAccess>);

template <typename SystemType>
[[nodiscard]]SystemType const& getSystem(htps::rptr<ISystemProvider const>);

template <typename SystemType>
[[nodiscard]]SystemType& getSystem(htps::rptr<ISystemProvider>);

template <typename SystemType>
[[nodiscard]]SystemType const& getSystem(htps::rptr<scene::SceneNode const>);

template <typename SystemType>
[[nodiscard]]SystemType& getSystem(htps::rptr<scene::SceneNode>);
}  // namespace haf::sys

#endif
