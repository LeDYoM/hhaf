#ifndef HAF_WINDOW_FPS_COUNTER_INCLUDE_HPP
#define HAF_WINDOW_FPS_COUNTER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <haf/include/time/time_point.hpp>

namespace haf::backend
{
    class IWindow;
}

namespace haf::sys
{
struct HAF_PRIVATE FPSCounter
{
    time::TimePoint lastTimeFps{0U};
    htps::fast_u16 lastFps{0U};
    htps::fast_u16 currentFps{0U};

    void updateFPS(time::TimePoint const& time_since_start,
                   htps::rptr<backend::IWindow> backend_window,
                   htps::str const& base_title);
};

}  // namespace haf::sys

#endif
