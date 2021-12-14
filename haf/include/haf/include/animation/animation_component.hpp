#ifndef HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/animation/animation.hpp>
#include <haf/include/animation/property_animation.hpp>
#include <haf/include/animation/property_animation_builder.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/system/datawrappercreator.hpp>
#include <haf/include/time/timercomponent.hpp>
#include <haf/include/time/timerconnector.hpp>
#include <htypes/include/properties.hpp>

namespace haf::anim
{
/**
 * @brief Component designed to store, manage and update animations.
 */
class AnimationComponent final : public component::IComponent
{
public:
    AnimationComponent();
    ~AnimationComponent() override;

    void update() override;

    /**
     * @brief Add an animation that animates a certain property of the node.
     * @param builder Builder containing the data
     */
    template <typename PropertyTag, typename SceneNodeType>
    void addAnimation(PropertyAnimationData<PropertyTag, SceneNodeType>&& data)
    {
        addAnimation(htps::muptr<PropertyAnimation<PropertyTag, SceneNodeType>>(
            std::move(data)));
    }

    template <typename PropertyTag, typename SceneNodeType>
    void addAnimation(
        PropertyAnimationBuilder<PropertyTag, SceneNodeType>&& builder)
    {
        addAnimation(builder.extract());
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_data(types::rptr<PropertyContainer> scene_node)
    {
        auto builder{PropertyAnimationData<PropertyTag, PropertyContainer>()};
        builder
            .prop<PropertyAnimationPropertiesSingle<PropertyTag,
                                                    PropertyContainer>>()
            .put<SceneNodeType<PropertyContainer>>(scene_node);

        builder.prop<AnimationProperties>()
            .put<TimerProperty>(attachedNode()
                                    ->component<time::TimerComponent>()
                                    ->addFreeTimer())
            .put<Times>(1);
        return builder;
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_data(types::sptr<PropertyContainer> scene_node)
    {
        return make_property_animation_data<PropertyTag, PropertyContainer>(
            scene_node.get());
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_data_from_attached()
    {
        return make_property_animation_data<PropertyTag, PropertyContainer>(
            attachedNodeAs<PropertyContainer>());
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_builder(
        types::rptr<PropertyContainer> scene_node)
    {
        return PropertyAnimationBuilder<PropertyTag, PropertyContainer>{
            make_property_animation_data<PropertyTag, PropertyContainer>(
                std::move(scene_node))};
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_builder(
        types::sptr<PropertyContainer> scene_node)
    {
        return make_property_animation_builder<PropertyTag, PropertyContainer>(
            scene_node.get());
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_builder_from_attached()
    {
        return PropertyAnimationBuilder<PropertyTag, PropertyContainer>{
            make_property_animation_data_from_attached<PropertyTag,
                                                       PropertyContainer>()};
    }

private:
    /**
     * @brief Add an already created animation to the list of animations.
     */
    void addAnimation(htps::uptr<Animation>);

    class AnimationComponentPrivate;
    htps::uptr<AnimationComponentPrivate> p_;
};

}  // namespace haf::anim

#endif
