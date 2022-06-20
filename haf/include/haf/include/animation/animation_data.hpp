HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties/basic_property.hpp>

#include <haf/include/time/time_point.hpp>
#include <haf/include/time/timer_connector.hpp>

namespace haf::anim
{
enum class AnimationDirection : htps::u8
{
    Forward  = 0U,  //< Animate increasing the delta value
    Backward = 1U,  //< Animate decreasing the delta value
};

struct AnimationProperties
{
    /**
     * @brief Timer to use in the animation
     */
    htps::BasicProperty<time::TimerConnectorSPtr> TimerProperty;
    /**
     * @brief Time computing the duration of the animation
     */
    htps::BasicProperty<time::TimePoint> Duration;

    htps::BasicProperty<htps::function<void()>> ActionWhenFinished;
    /**
     * @brief Direction of the animation
     */
    htps::BasicProperty<AnimationDirection> AnimationDirectionProperty;
    /**
     * @brief Number of times to perform the animation
     */
    htps::BasicProperty<htps::s32> Times;

    /**
     * @brief Switch between forward and backward
     */
    htps::BasicProperty<bool> Switch;
};

}  // namespace haf::anim

#endif
