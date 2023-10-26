#include "scene_manager subsystem_group.hpp"
#include "iscene_manager subsystem.hpp"

using namespace haf::core;

namespace haf::scene
{
void SceneManagerSubSystemGroup::add(uptr<ISceneManagerSubSystem> ss)
{
    m_sub_systems_group.push_back(core::move(ss));
}

vector<uptr<ISceneManagerSubSystem>> const&
SceneManagerSubSystemGroup::subsystems() const noexcept
{
    return m_sub_systems_group;
}

}  // namespace haf::scene
