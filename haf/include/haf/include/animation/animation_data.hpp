#ifndef HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP

#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timeview.hpp>
#include <haf/include/time/timer.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/function.hpp>

namespace haf::anim
{
/**
 * @brief Type to represent an animation
 */
using ActionFunc = htps::function<void()>;

enum class AnimationDirection : htps::u8
{
    Forward = 0U,
    Backward
};

class AnimationData
{
public:
    htps::uptr<time::Timer> timer_;
    time::TimePoint duration_;
    ActionFunc end_action_;
    AnimationDirection animation_direction_;
};

}  // namespace haf::anim

#endif
