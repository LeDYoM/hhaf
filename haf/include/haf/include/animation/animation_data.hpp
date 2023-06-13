HAF_PRAGMA_ONCE
#ifndef HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/basic_property.hpp>

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
    prop::BasicProperty<time::TimerConnectorSPtr> TimerProperty;
    /**
     * @brief Time computing the duration of the animation
     */
    prop::BasicProperty<time::TimePoint> Duration;

    prop::BasicProperty<htps::function<void()>> ActionWhenFinished;
    /**
     * @brief Direction of the animation
     */
    prop::BasicProperty<AnimationDirection> AnimationDirectionProperty;
    /**
     * @brief Number of times to perform the animation
     */
    prop::BasicProperty<htps::s32> Times;

    /**
     * @brief Switch between forward and backward
     */
    prop::BasicProperty<bool> Switch;
};

}  // namespace haf::anim

#endif
