#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/animation/property_animation_data.hpp>

namespace haf::anim
{
template <typename PropertyTag, typename SceneNodeT>
class PropertyAnimationBuilder
{
public:
    PropertyAnimationBuilder() = default;

    explicit PropertyAnimationBuilder(
        PropertyAnimationData<PropertyTag, SceneNodeT> data) :
        data_{std::move(data)}
    {}

    PropertyAnimationBuilder& startValue(
        StartValue<PropertyTag>::value_type value)
    {
        data_.prop<StartValue<PropertyTag>>() = std::move(value);
        return *this;
    }

    PropertyAnimationBuilder& endValue(EndValue<PropertyTag>::value_type value)
    {
        data_.prop<EndValue<PropertyTag>>() = std::move(value);
        return *this;
    }

    PropertyAnimationBuilder& duration(Duration::value_type value)
    {
        data_.prop<Duration>() = std::move(value);
        return *this;
    }

    PropertyAnimationBuilder& times(Times::value_type value)
    {
        data_.prop<Times>() = std::move(value);
        return *this;
    }

    PropertyAnimationBuilder& switchAnimation(Switch::value_type value)
    {
        data_.prop<Switch>() = std::move(value);
        return *this;
    }

    PropertyAnimationBuilder& continuous()
    {
        return times(-1);
    }

    PropertyAnimationBuilder& actionWhenFinished(
        ActionWhenFinished::value_type value)
    {
        data_.prop<ActionWhenFinished>() = std::move(value);
        return *this;
    }

    PropertyAnimationData<PropertyTag, SceneNodeT>&& extract() noexcept
    {
        return std::move(data_);
    }

private:
    PropertyAnimationData<PropertyTag, SceneNodeT> data_;
};

}  // namespace haf::anim

#endif
