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
    /*
     * @param timer @b Timer to use to animate
     * @param duration @b time::TimePoint containing the time the animation is
     *  going to last
     * @param animation_direction @b AnimationDirection Direction of the
     *  animation
     * @param endAction Functor containing an action to perform when the
     *  animation finishes
     */

    htps::uptr<time::Timer> timer_;  //< Timer to use to animate
    time::TimePoint duration_;  //< @b time::TimePoint containing the time the
                                // animation is going to last
    ActionFunc end_action_;     //< Functor containing an action to perform when
                                // the animation finishes
    AnimationDirection animation_direction_{
        AnimationDirection::Forward};  //< Direction of the animation
    AnimationCountMode animation_count_mode_{
        AnimationCountMode::FixedCount};  //< Option specifying if the animation
                                          //is going to be performed only once
                                          //or a conted number.
    AnimationDeltaMode animation_delta_mode_{AnimationDeltaMode::Linear};
    htps::size_type times_{1U};
};

}  // namespace haf::anim

#endif
