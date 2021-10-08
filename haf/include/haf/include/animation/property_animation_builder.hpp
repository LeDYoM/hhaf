#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/animation/property_animation_data.hpp>

namespace haf::anim
{
/**
 * @brief Builder class to help the creation of animations. It wraps
 * a @b PropertyAnimationData<PropertyTag, SceneNodeT> and modifies
 * it providing an easy interface.
 * @tparam PropertyTag Tag fpr the property
 * @tparam SceneNodeT Type of the SceneNode to animate
 */
template <typename PropertyTag, typename SceneNodeT>
class PropertyAnimationBuilder
{
public:
    /**
     * @brief Construct a new Property Animation Builder object
     * @param data An already created @b PropertyAnimationData
     */
    explicit PropertyAnimationBuilder(
        PropertyAnimationData<PropertyTag, SceneNodeT> data) :
        data_{std::move(data)}
    {}

    PropertyAnimationBuilder& startValue(
        StartValue<PropertyTag>::value_type const& value)
    {
        data_.prop<StartValue<PropertyTag>>() = value;
        return *this;
    }

    /**
     * @brief Set the Startvalue property of the animation to the current value
     * for the property in the SceneNodeType object attached.
     * @note Set the scene node object first.
     *
     * @return PropertyAnimationBuilder& The current builder
     */
    PropertyAnimationBuilder& startValueIsCurrent()
    {
        data_.prop<StartValue<PropertyTag>>() =
            data_.prop<SceneNodeType<SceneNodeT>>()()
                ->template prop<PropertyTag>()();
        return *this;
    }

    /**
     * @brief Set the EndValue property of the animation to the current value
     * for the property in the SceneNodeType object attached.
     * @note Set the scene node object first.
     *
     * @return PropertyAnimationBuilder& The current builder
     */
    PropertyAnimationBuilder& endValueIsCurrent()
    {
        data_.prop<EndValue<PropertyTag>>() =
            data_.prop<SceneNodeType<SceneNodeT>>()()
                ->template prop<PropertyTag>()();
        return *this;
    }

    PropertyAnimationBuilder& endValue(
        EndValue<PropertyTag>::value_type const& value)
    {
        data_.prop<EndValue<PropertyTag>>() = value;
        return *this;
    }

    PropertyAnimationBuilder& duration(Duration::value_type const& value)
    {
        data_.prop<Duration>() = value;
        return *this;
    }

    PropertyAnimationBuilder& times(Times::value_type const& value)
    {
        data_.prop<Times>() = value;
        return *this;
    }

    PropertyAnimationBuilder& switchAnimation(Switch::value_type const& value)
    {
        data_.prop<Switch>() = value;
        return *this;
    }

    PropertyAnimationBuilder& continuous() { return times(-1); }

    PropertyAnimationBuilder& actionWhenFinished(
        ActionWhenFinished::value_type const& value)
    {
        data_.prop<ActionWhenFinished>() = value;
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
