HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_PASS_MANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENE_PASS_MANAGER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include "haf_private.hpp"
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component.hpp>

#include "iscene_subsystem.hpp"

namespace haf::scene
{
class HAF_PRIVATE ScenePassManager final
{
public:
    void registerScenePassSubsystem(core::sptr<ISceneSubsystem>);

    void registerForPass(htps::str_view passName,
                         htps::sptr<component::Component> node);
private:
    core::Dictionary<core::sptr<ISceneSubsystem>> m_scene_subsystems;
};

}  // namespace haf::scene

#endif
