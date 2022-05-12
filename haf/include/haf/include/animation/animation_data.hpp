HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/property_group.hpp>

#include <haf/include/time/time_point.hpp>
#include <haf/include/time/timer_connector.hpp>

namespace haf::anim
{
/**
 * @brief Type to represent an animation
 */
struct ActionWhenFinished : htps::BasicPropertyBase<htps::function<void()>>
{};

enum class AnimationDirection : htps::u8
{
    Forward  = 0U,  //< Animate increasing the delta value
    Backward = 1U,  //< Animate decreasing the delta value
};

/**
 * @brief Direction of the animation
 */
struct AnimationDirectionProperty : htps::BasicPropertyBase<AnimationDirection>
{};

/**
 * @brief Timer to use in the animation
 */
struct TimerProperty : htps::BasicPropertyBase<time::TimerConnectorSPtr>
{};

/**
 * @brief Time computing the duration of the animation
 */
struct Duration : htps::BasicPropertyBase<time::TimePoint>
{};

/**
 * @brief Number of times to perform the animation
 */
struct Times : htps::BasicPropertyBase<htps::s32>
{};

/**
 * @brief Switch between forward and backward
 */
struct Switch : htps::BasicPropertyBase<bool>
{};

using AnimationProperties = htps::PropertyGroup<TimerProperty,
                                                Duration,
                                                ActionWhenFinished,
                                                AnimationDirectionProperty,
                                                Times,
                                                Switch>;
}  // namespace haf::anim

#endif
