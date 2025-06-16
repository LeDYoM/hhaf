HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_SUBSYSTEM_INCLUDE_HPP
#define HAF_SCENE_SCENE_SUBSYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include "haf_private.hpp"
#include "component_type_updater.hpp"

namespace haf::scene
{
class HAF_PRIVATE ISceneSubsystem
{
public:
    virtual htps::str const& getName() const = 0;
};

}  // namespace haf::scene

#endif
