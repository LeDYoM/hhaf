#include "iscene_manager subsystem.hpp"
#include <haf/include/component/component_updater.hpp>

using namespace haf::core;

namespace haf::scene
{
ISceneManagerSubSystem::ISceneManagerSubSystem(str subsystem_name) :
    m_subsystem_name{core::move(subsystem_name)}
{}

ISceneManagerSubSystem::~ISceneManagerSubSystem() = default;

bool ISceneManagerSubSystem::isComponentAcceptable(
    component::ComponentUpdater& component_updater)
{
    (void)(component_updater);
    return true;
    //    return subSystemName() == component_updater.parentSubSystemName();
}

void ISceneManagerSubSystem::performUpdateAction(component::ComponentUpdater&)
{}

}  // namespace haf::scene
