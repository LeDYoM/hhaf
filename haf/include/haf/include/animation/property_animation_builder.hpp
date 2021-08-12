#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/property_animation_data.hpp>
#include <haf/include/animation/animation_builder.hpp>
#include <haf/include/time/timer.hpp>

namespace haf::anim
{
template <typename T, typename Tag>
class PropertyAnimationBuilder
{
private:
    AnimationBuilder base_animation_builder_;

public:
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

    AnimationBuilder& baseBuilder() { return base_animation_builder_; }

private:
    PropertyAnimationData<T, Tag> data_;
};

}  // namespace haf::anim

#endif
