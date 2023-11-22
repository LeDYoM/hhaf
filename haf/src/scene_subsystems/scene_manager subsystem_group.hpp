HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENEMANAGER_SUBSYSTEM_GROUP_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_SUBSYSTEM_GROUP_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>
#include "iscene_manager subsystem.hpp"

namespace haf::scene
{
class SceneManagerSubSystemGroup
{
public:
    void add(core::uptr<ISceneManagerSubSystem> ss);

    core::vector<core::uptr<ISceneManagerSubSystem>> const& subsystems()
        const noexcept;

private:
    core::vector<core::uptr<ISceneManagerSubSystem>> m_sub_systems_group;
};
}  // namespace haf::scene

#endif
