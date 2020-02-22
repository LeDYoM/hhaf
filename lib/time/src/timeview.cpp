#include <lib/time/include/timeview.hpp>

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/time/i_include/timesystem.hpp>
#include <lib/system/systemprovider.hpp>

namespace lib::time
{
TimePoint TimeView::now() const
{
    return attachedNode()->sceneManager().systemProvider().timeSystem().now();
}

} // namespace lib::scene
