#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/property_animation_data.hpp>
#include <haf/include/animation/animation_builder.hpp>
#include <haf/include/time/timer.hpp>

namespace haf::anim
{
/**
 * @brief Class to build a property animation
 * 
 * @tparam T Type of the property to animate
 * @tparam Tag Type tag of the property to animate
 */
template <typename T, typename Tag>
class PropertyAnimationBuilder
{
private:
    AnimationBuilder base_animation_builder_;

public:
    PropertyAnimationBuilder& duration(time::TimePoint duration)
    {
        base_animation_builder_.duration(std::move(duration));
        return *this;
    }

    PropertyAnimationBuilder& endAction(ActionFunc end_action)
    {
        base_animation_builder_.endAction(std::move(end_action));
        return *this;
    }

    PropertyAnimationBuilder& animationDirection(
        AnimationDirection animation_direction)
    {
        base_animation_builder_.animationDirection(
            std::move(animation_direction));
        return *this;
    }

    PropertyAnimationBuilder& timer(htps::uptr<time::Timer> timer)
    {
        base_animation_builder_.timer(std::move(timer));
        return *this;
    }

    PropertyAnimationBuilder& property(htps::IProperty<T, Tag>* property)
    {
        data_.property_ = std::move(property);
        return *this;
    }

    PropertyAnimationBuilder& startValue(T start_value)
    {
        data_.startValue_ = std::move(start_value);
        return *this;
    }

    PropertyAnimationBuilder& endValue(T end_value)
    {
        data_.endValue_ = std::move(end_value);
        return *this;
    }

    PropertyAnimationData<T, Tag> extractData() { return std::move(data_); }
    AnimationData extractBaseData()
    {
        return std::move(base_animation_builder_.extractData());
    }

private:
    PropertyAnimationData<T, Tag> data_;
};

}  // namespace haf::anim

#endif
