#include "input_subsystem"

using namespace haf::core;

namespace haf::scene
{
InputSubSystem::InputSubSystem() : ISceneManagerSubSystem{"Input"} {}

ISceneManagerSubSystem::ISceneManagerSubSystem(str subsystem_name) :
    m_subsystem_name{core::move(subsystem_name)}
{}

bool ISceneManagerSubSystem::update(
    component::ComponentUpdater& component_updater)
{
    component_updater.update(*this);
    return true;
}

}  // namespace haf::scene
