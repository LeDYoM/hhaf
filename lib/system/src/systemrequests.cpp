#include "systemrequests.hpp"
#include "systemaccess.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/system/i_include/systemprovider.hpp>
#include <lib/system/i_include/get_systemprovider.hpp>

namespace lib::sys
{
void SystemRequests::requestExit()
{
    getSystemProvider(attachedNode()->isystemProvider()).requestExit();
}

bool SystemRequests::exitRequested() const
{
    return getSystemProvider(attachedNode()->isystemProvider()).exitRequested();
}

} // namespace lib::sys
