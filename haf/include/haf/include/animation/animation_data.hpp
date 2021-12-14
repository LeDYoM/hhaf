#ifndef HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP

#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timerconnector.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/property_group.hpp>

namespace haf::anim
{
/**
 * @brief Type to represent an animation
 */
struct ActionWhenFinished : BasicPropertyBase<htps::function<void()>>
{};

enum class AnimationDirection : htps::u8
{
    Forward  = 0U,  //< Animate increasing the delta value
    Backward = 1U,  //< Animate decreasing the delta value
};

/**
 * @brief Direction of the animation
 */
struct AnimationDirectionProperty : BasicPropertyBase<AnimationDirection>
{};

/**
 * @brief Timer to use in the animation
 */
struct TimerProperty : BasicPropertyBase<time::TimerConnectorSPtr>
{};

/**
 * @brief Time computing the duration of the animation
 */
struct Duration : BasicPropertyBase<time::TimePoint>
{};

/**
 * @brief Number of times to perform the animation
 *
 */
struct Times : BasicPropertyBase<types::s32>
{};

/**
 * @brief Switch between forward and backward
 */
struct Switch : BasicPropertyBase<bool>
{};

using AnimationProperties = types::PropertyGroup<TimerProperty,
                                                 Duration,
                                                 ActionWhenFinished,
                                                 AnimationDirectionProperty,
                                                 Times,
                                                 Switch>;
}  // namespace haf::anim

#endif
