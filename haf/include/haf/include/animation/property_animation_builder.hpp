#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/property_animation_data.hpp>
#include <haf/include/animation/animation_builder.hpp>

namespace haf::anim
{
template <typename T, typename Tag>
class PropertyAnimationBuilder : public AnimationBuilder
{
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

    PropertyAnimationData<T, Tag> propertyAnimationData() noexcept
    {
        return data_;
    }
private:
    PropertyAnimationData<T, Tag> data_;
};
}  // namespace haf::anim

#endif
