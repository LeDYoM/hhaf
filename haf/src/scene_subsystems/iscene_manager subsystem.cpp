#include "iscene_manager subsystem.hpp"
#include <haf/include/component/component_updater.hpp>

using namespace haf::core;

namespace haf::scene
{
ISceneManagerSubSystem::ISceneManagerSubSystem(str subsystem_name) :
    m_subsystem_name{core::move(subsystem_name)}
{}

ISceneManagerSubSystem::~ISceneManagerSubSystem() = default;

bool ISceneManagerSubSystem::update(
    component::ComponentUpdater& component_updater)
{
    component_updater.update(*this);
    return true;
}

}  // namespace haf::scene
