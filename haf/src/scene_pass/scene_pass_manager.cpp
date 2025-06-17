#include "scene_pass_manager.hpp"

using namespace haf::core;

namespace haf::scene
{
void ScenePassManager::registerScenePassSubsystem(
    sptr<ISceneSubsystem> scene_pass)
{
    (void)(m_scene_subsystems.add(scene_pass->getName(),
                                  std::move(scene_pass)));
}

void ScenePassManager::registerForPass(
    htps::str_view /*passName*/,
    htps::sptr<component::Component> /*node*/)
{}

}  // namespace haf::scene
