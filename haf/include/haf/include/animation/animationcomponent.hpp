#ifndef HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/time/timeview.hpp>
#include <haf/include/animation/animation.hpp>
#include <haf/include/animation/propertyanimation.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/system/datawrappercreator.hpp>
#include <htypes/include/properties.hpp>

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
     * @brief Add an already created animation to the list of animations.
     */
    void addAnimation(htps::uptr<Animation>);

    /**
     * @brief Add an animation that animates a certain property of the node.
     * @param builder Builder containing the data
     */
    template <typename T, typename PropertyTag>
    void addAnimation(
        htps::uptr<PropertyAnimationBuilder<T, PropertyTag>> builder)
    {
        auto anim = htps::muptr<IPropertyAnimation<T, PropertyTag>>(
            builder->extractBaseData(), builder->extractData());

        addAnimation(std::move(anim));
    }

    template <typename T, typename PropertyTag>
    htps::uptr<PropertyAnimationBuilder<T, PropertyTag>>
    make_property_animation_builder(htps::IProperty<T, PropertyTag>& property,
                                    htps::uptr<time::Timer> timer = nullptr)
    {
        if (timer == nullptr)
        {
            timer = attachedNode()->subsystems().dataWrapper<time::Timer>();
        }

        auto builder = htps::muptr<PropertyAnimationBuilder<T, PropertyTag>>();
        builder->property(&property).timer(std::move(timer));
        return builder;
    }

private:
    class AnimationComponentPrivate;
    htps::uptr<AnimationComponentPrivate> p_;
};
}  // namespace haf::anim

#endif
