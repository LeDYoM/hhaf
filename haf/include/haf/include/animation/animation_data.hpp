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
};

enum class AnimationDeltaMode : htps::u8
{
    Linear = 0U,  //< Update the delta value in a linear way
};

class AnimationData
{
public:
    htps::uptr<time::Timer> timer_;  //< Timer to use to animate
    time::TimePoint duration_;  //< @b time::TimePoint containing the time the
                                // animation is going to last
    ActionFunc end_action_;     //< Functor containing an action to perform when
                                //< the animation finishes
    AnimationDirection animation_direction_{
        AnimationDirection::Forward};  //< Direction of the animation
    AnimationDeltaMode animation_delta_mode_{
        AnimationDeltaMode::Linear};  //< Select equation to update the delta
                                      // value
    htps::s32 times_{1U};  //< Number of times to perform the animation
    bool switch_{false};   //< Switch between forward and backward
};

}  // namespace haf::anim

#endif
