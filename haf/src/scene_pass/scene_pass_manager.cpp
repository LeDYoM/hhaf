#include "scene_pass_manager.hpp"

namespace haf::scene
{
void ScenePassManager::registerSceneSubsystem(ISceneSubsystem&)
{}

void ScenePassManager::registerForPass(htps::str_view /*passName*/,
                                       htps::sptr<component::Component> /*node*/)
{}

}  // namespace haf::scene
