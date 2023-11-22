HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_ISCENEMANAGER_SUBSYSTEM_RENDER_SUBSYSTEM_INCLUDE_HPP
#define HAF_SCENE_ISCENEMANAGER_SUBSYSTEM_RENDER_SUBSYSTEM_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>
#include "iscene_manager subsystem.hpp"

namespace haf::scene
{
class RenderSubSystem final : public ISceneManagerSubSystem
{
public:
    RenderSubSystem();
};
}  // namespace haf::scene

#endif
