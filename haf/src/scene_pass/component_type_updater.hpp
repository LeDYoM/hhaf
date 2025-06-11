HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_COMPONENT_TYPE_UPDATER_INCLUDE_HPP
#define HAF_SCENE_COMPONENT_TYPE_UPDATER_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::scene
{
template <typename ComponentTypeInput, typename ComponentTypeOutput>
class ComponentTypeUpdater
{
    virtual void update(ComponentTypeInput const& input,
                        ComponentTypeOutput& output) = 0;
};

}  // namespace haf::scene

#endif
