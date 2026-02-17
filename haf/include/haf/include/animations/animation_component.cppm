HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP

import :animation;
import :components:component;
import :property_animation;
import :property_animation_builder;
import :scene:scene_node;
import :time:timer_component;
import :time:timer_connector;
import :properties:iproperty;
import :components:component;
import :core:log;
import :core:types;

namespace haf::anim
{
class AnimationComponent::AnimationComponentPrivate
{
public:
    AnimationComponentPrivate() {}
    LockableVector<sptr<Animation>> animations_;

    void addAnimation(PropertyAnimationData&& data)
    {
        addAnimation(htps::muptr<PropertyAnimation>(htps::move(data)));
    }

    void addAnimation(uptr<Animation> nanimation)
    {
        animations_.push_back(htps::move(nanimation));
    }
};

/**
 * @brief Component designed to store, manage and update animations.
 */
class AnimationComponent final : public component::Component
{
public:
    AnimationComponent() : p_{muptr<AnimationComponentPrivate>()} {}

    ~AnimationComponent() override = delete;

    void update() override
    {
        p_->animations_.performUpdate([this](auto& animation) {
            if (!animation->animate())
            {
                animation->executeEndAction();
                p_->animations_.erase_value(animation);
            }
        });
    }

    /**
     * @brief Add an animation that animates a certain property of the node.
     * @param builder Builder containing the data
     */
    void addAnimation(PropertyAnimationBuilder&& builder)
    {
        p_->addAnimation(builder.extract());
    }

    PropertyAnimationBuilder make_property_animation_builder()
    {
        return PropertyAnimationBuilder{make_property_animation_data()};
    }

    template <typename T,
              template <typename> typename PropertyType,
              typename PropertyValue>
    PropertyAnimationBuilder make_property_animation_builder(
        PropertyType<PropertyValue>(T::* property_v),
        PropertyValue const& start_value,
        PropertyValue const& end_value)
    {
        auto builder{make_property_animation_builder()};
        auto animateComponent{attachedNode()->componentOfType<T>()};
        HAF_ASSERT(animateComponent != nullptr);
        builder.deltaProperty(make_delta_property(
            animateComponent.get(), property_v, start_value, end_value));
        return builder;
    }

private:
    PropertyAnimationData make_property_animation_data()
    {
        PropertyAnimationData property_animation_data{};
        property_animation_data.TimerProperty =
            attachedNode()->component<time::TimerComponent>()->addFreeTimer();
        property_animation_data.Times = 1;
        return property_animation_data;
    }

    class AnimationComponentPrivate;
    htps::uptr<AnimationComponentPrivate> p_;
};

}  // namespace haf::anim
