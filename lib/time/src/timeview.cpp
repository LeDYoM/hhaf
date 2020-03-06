#include <lib/time/include/timeview.hpp>

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/time/i_include/timesystem.hpp>
#include <lib/system/i_include/systemprovider.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace lib::time
{
TimePoint TimeView::now() const
{
    
    return sys::getSystem<sys::TimeSystem>(attachedNode()).now();
}

} // namespace lib::scene
