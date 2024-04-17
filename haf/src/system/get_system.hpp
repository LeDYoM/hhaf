HAF_PRAGMA_ONCE
#ifndef HAF_SYSTEM_INTERNAL_GET_INCLUDE_HPP
#define HAF_SYSTEM_INTERNAL_GET_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::sys
{
class SystemAccess;
class ISystemProvider;

template <typename SystemType>
[[nodiscard]] SystemType const& getSystem(core::rptr<SystemAccess const>);

template <typename SystemType>
[[nodiscard]]SystemType& getSystem(core::rptr<SystemAccess>);

template <typename SystemType>
[[nodiscard]]SystemType const& getSystem(core::rptr<ISystemProvider const>);

template <typename SystemType>
[[nodiscard]]SystemType& getSystem(core::rptr<ISystemProvider>);

template <typename SystemType>
[[nodiscard]]SystemType const& getSystem(htps::rptr<scene::SceneNode const>);

template <typename SystemType>
[[nodiscard]]SystemType& getSystem(core::rptr<scene::SceneNode>);
}  // namespace haf::sys

#endif
