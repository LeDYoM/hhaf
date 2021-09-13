#ifndef HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/animation/animation.hpp>
#include <haf/include/animation/property_animation.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/system/datawrappercreator.hpp>
#include <htypes/include/properties.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::anim
{
/**
 * @brief Component designed to store, manage and update animations.
 */
class AnimationComponent : public component::IComponent
{
public:
    AnimationComponent();
    ~AnimationComponent() override;

    void update() override;

    /**
     * @brief Add an animation that animates a certain property of the node.
     * @param builder Builder containing the data
     */
    template <typename T, typename PropertyTag, typename SceneNodeType>
    void addAnimation(
        htps::uptr<PropertyAnimationBuilder<T, PropertyTag, SceneNodeType>>
            builder)
    {
        addAnimation(htps::muptr<PropertyAnimation<T, PropertyTag, SceneNodeType>>(
            builder->extractBaseData(), builder->extractData()));
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_builder(PropertyContainer& scene_node)
    {
        auto builder = htps::muptr<PropertyAnimationBuilder<
            typename PropertyTag::value_type, PropertyTag, PropertyContainer>>();
        builder->property(&(scene_node.prop<PropertyTag>()))
            .timer(attachedNode()->subsystems().dataWrapper<time::Timer>());
        builder->node(&scene_node);
        return builder;
    }

    template <typename PropertyTag, typename PropertyContainer>
    auto make_property_animation_builder(
        htps::sptr<PropertyContainer> scene_node)
    {
        return make_property_animation_builder<PropertyTag, PropertyContainer>(
            *scene_node);
    }

    template <typename PropertyTag, typename PropertyGroupType>
    auto make_property_animation_builder2(
        htps::sptr<PropertyGroupType> scene_node)
    {
        return make_property_animation_builder<PropertyTag, PropertyGroupType>(
            *scene_node);
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
