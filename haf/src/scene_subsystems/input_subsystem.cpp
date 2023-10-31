#include "input_subsystem.hpp"
#include <haf/include/component/component_updater.hpp>

using namespace haf::core;

namespace haf::scene
{
InputSubSystem::InputSubSystem() : ISceneManagerSubSystem{"Input"} {}

bool InputSubSystem::update(
    component::ComponentUpdater& component_updater)
{
    component_updater.update(*this);
    return true;
}

}  // namespace haf::scene
