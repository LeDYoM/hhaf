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
    Forward  = 0U,  //< Animate increasing the delta value
    Backward = 1U,  //< Animate decreasing the delta value
    Circling =
        2U,  //< Animate switching direction when arriving to the end value
};

enum class AnimationCountMode : htps::u8
{
    FixedCount = 0U,  //< Perform animation times_ times
    Continuous = 1U,  //< Perform animation continuous
};

enum class AnimationDeltaMode : htps::u8
{
    Linear = 0U,  //< Update the delta value in a linear way
};

class AnimationData
{
public:
    htps::uptr<time::Timer> timer_;
    time::TimePoint duration_;
    ActionFunc end_action_;
    AnimationDirection animation_direction_{AnimationDirection::Forward};
    AnimationCountMode animation_count_mode_{AnimationCountMode::FixedCount};
    AnimationDeltaMode animation_delta_mode_{AnimationDeltaMode::Linear};
    htps::size_type times_{1U};
};

}  // namespace haf::anim

#endif
