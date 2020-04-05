#include <lib/time/include/timeview.hpp>

#include <lib/scene/include/scenenode.hpp>
#include <lib/time/i_include/timesystem.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace haf::time
{
TimePoint TimeView::now() const
{
    
    return sys::getSystem<sys::TimeSystem>(attachedNode()).now();
}

} // namespace haf::scene
