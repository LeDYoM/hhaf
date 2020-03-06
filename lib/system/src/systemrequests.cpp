#include "systemrequests.hpp"
#include <lib/scene/include/scenemanager.hpp>
#include <lib/system/i_include/systemprovider.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace lib::sys
{
void SystemRequests::requestExit()
{
    sys::getSystem<scene::SceneManager>(attachedNode()).systemProvider().requestExit();
}

bool SystemRequests::exitRequested() const
{
    return sys::getSystem<scene::SceneManager>(attachedNode()).systemProvider().exitRequested();
}

} // namespace lib::sys
