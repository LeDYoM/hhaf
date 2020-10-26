#include <haf/time/include/timeview.hpp>
#include <haf/time/i_include/timesystem.hpp>

#include <haf/scene/include/scenenode.hpp>

#include <system/i_include/get_system.hpp>

namespace haf::time
{
TimePoint TimeView::now() const
{

    return sys::getSystem<sys::TimeSystem>(attachedNode()).now();
}

}  // namespace haf::time
