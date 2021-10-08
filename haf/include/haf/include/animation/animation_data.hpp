#ifndef HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_DATA_INCLUDE_HPP

#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timeview.hpp>
#include <haf/include/time/timer.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/property_group.hpp>

namespace haf::anim
{
/**
 * @brief Type to represent an animation
 */
struct ActionWhenFinished
{
    using value_type = htps::function<void()>;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

enum class AnimationDirection : htps::u8
{
    Forward  = 0U,  //< Animate increasing the delta value
    Backward = 1U,  //< Animate decreasing the delta value
};

/**
 * @brief Direction of the animation
 */
struct AnimationDirectionProperty
{
    using value_type = AnimationDirection;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

/**
 * @brief Timer to use in the animation
 */
struct TimerProperty
{
    using value_type = types::sptr<time::Timer>;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

/**
 * @brief Time computing the duration of the animation
 */
struct Duration
{
    using value_type = time::TimePoint;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

/**
 * @brief Number of times to perform the animation
 *
 */
struct Times
{
    using value_type = types::s32;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

/**
 * @brief Switch between forward and backward
 */
struct Switch
{
    using value_type = bool;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

using AnimationProperties = types::PropertyGroup<TimerProperty,
                                                 Duration,
                                                 ActionWhenFinished,
                                                 AnimationDirectionProperty,
                                                 Times,
                                                 Switch>;
}  // namespace haf::anim

#endif
