#include <haf/time/include/timeview.hpp>

#include <haf/scene/include/scenenode.hpp>
#include <haf/time/i_include/timesystem.hpp>
#include <haf/system/i_include/get_system.hpp>

namespace haf::time
{
TimePoint TimeView::now() const
{
    
    return sys::getSystem<sys::TimeSystem>(attachedNode()).now();
}

} // namespace haf::scene
