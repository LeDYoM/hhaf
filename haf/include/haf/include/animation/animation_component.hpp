HAF_PRAGMA_ONCE
#ifndef HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/animation/animation.hpp>
#include <haf/include/animation/property_animation.hpp>
#include <haf/include/animation/property_animation_builder.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/time/timer_component.hpp>
#include <haf/include/time/timer_connector.hpp>
#include <haf/include/properties/iproperty.hpp>

namespace haf::anim
{
/**
 * @brief Component designed to store, manage and update animations.
 */
class AnimationComponent final
    : public component::ComponentBootStrap<AnimationComponent>
{
public:
    static constexpr const core::str_view StaticTypeName{
        "AnimationComponent"};

    AnimationComponent();
    ~AnimationComponent() override;

    void updateAnimation();

    /**
     * @brief Add an animation that animates a certain property of the node.
     * @param builder Builder containing the data
     */
    void addAnimation(PropertyAnimationBuilder&& builder);

    PropertyAnimationBuilder make_property_animation_builder();

    template <template <typename> typename PropertyType,
              typename PropertyValue,
              typename ObjectType>
    PropertyAnimationBuilder make_property_animation_builder(
        PropertyType<PropertyValue>(ObjectType::*property_v),
        PropertyValue const& start_value,
        PropertyValue const& end_value)
    {
        auto builder{make_property_animation_builder()};
        builder.deltaProperty(make_delta_property(
            attachedNodeAs<ObjectType>(), property_v, start_value, end_value));
        return builder;
    }

private:
    PropertyAnimationData make_property_animation_data();

    class AnimationComponentPrivate;
    htps::uptr<AnimationComponentPrivate> p_;
};

}  // namespace haf::anim

#endif
