#include "systemrequests.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/system/i_include/systemprovider.hpp>

namespace lib::sys
{
void SystemRequests::requestExit()
{
    attachedNode()->sceneManager().systemProvider().requestExit();
}

bool SystemRequests::exitRequested() const
{
    return attachedNode()->sceneManager().systemProvider().exitRequested();
}

} // namespace lib::sys
