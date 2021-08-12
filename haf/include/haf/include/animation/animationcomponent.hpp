#ifndef HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/time/timeview.hpp>
#include <haf/include/animation/animation.hpp>
#include <haf/include/animation/ipropertyanimation.hpp>
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
     *
     * @tparam PropertyType Type of the property to animate.
     * @param time Time that the animation will last.
     * @param property Reference of the instance to animate.
     * @param start Value to be set before starting the animation.
     * @param dest Destination value of the property
     * @param animation_direction Direction of the animation
     * @param endAction Action to perform when the animation finishes
     */
    template <typename PropertyType, typename PropertyTag>
    void addPropertyAnimation(
        time::TimePoint time,
        htps::IProperty<PropertyType, PropertyTag>& property,
        PropertyType start,
        PropertyType dest,
        AnimationDirection animation_direction = AnimationDirection::Forward,
        ActionFunc endAction                   = {})
    {
        auto anim = htps::muptr<IPropertyAnimation<PropertyType, PropertyTag>>(
            attachedNode()->subsystems().dataWrapper<time::Timer>(),
            std::move(time), property, std::move(start), std::move(dest),
            std::move(animation_direction), std::move(endAction));

        addAnimation(std::move(anim));
    }

    template <typename T, typename PropertyTag>
    void addAnimation(
        htps::uptr<PropertyAnimationBuilder<T, PropertyTag>> builder)
    {
        auto anim = htps::muptr<IPropertyAnimation<T, PropertyTag>>(
            builder->baseBuilder().extractData(), builder->extractData());

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

        auto builder = muptr<PropertyAnimationBuilder<T, PropertyTag>>();
        builder->property(&property).baseBuilder().timer(std::move(timer));
        return builder;
    }

    /**
     * @brief Add an animation that animates a certain property of the node.
     *  When the animation finishes, it starts again setting the property
     *  to start and repeating the process.
     *
     * @tparam PropertyType Type of the property to animate.
     * @param time Time that the animation will last.
     * @param property Reference of the instance to animate.
     * @param start Value to be set before starting the animation.
     * @param dest Destination value of the property.
     * @param animation_direction Direction of the animation
     * @param endAction Action to perform when the animation finishes.
     */
    template <typename PropertyType, typename PropertyTag>
    void addRepeatedPropertyAnimation(
        time::TimePoint time,
        htps::IProperty<PropertyType, PropertyTag>& property,
        PropertyType start,
        PropertyType dest,
        AnimationDirection animation_direction = AnimationDirection::Forward,
        ActionFunc endAction                   = {})
    {
        addPropertyAnimation(
            time, property, start, dest, animation_direction,
            [  // Capture this by reference
                this,
                // these properties by copy
                time, start, dest, animation_direction,
                                       // Reference to the property by reference
                                       & property = property,
                // Move endAction inside the inner lambda
                endAction = std::move(endAction)]() {
                if (endAction)
                {
                    endAction();
                }
                addRepeatedPropertyAnimation(time, property, start, dest,
                                             animation_direction,
                                             std::move(endAction));
            });
    }

    /**
     * @brief Add an animation that animates a certain property of the node.
     *  When the animation finishes, it starts again using the states currently
     *  set at the end of the animation.
     *
     * @tparam PropertyType Type of the property to animate.
     * @param time Time that the animation will last.
     * @param property Reference of the instance to animate.
     * @param dest Destination value of the property.
     * @param animation_direction Direction of the animation
     * @param endAction Action to perform when the animation finishes.
     */
    template <typename PropertyType, typename PropertyTag>
    void addCircledPropertyAnimation(
        time::TimePoint time,
        htps::IProperty<PropertyType, PropertyTag>& property,
        PropertyType start,
        PropertyType dest,
        AnimationDirection animation_direction = AnimationDirection::Forward,
        ActionFunc endAction                   = {})
    {
        addPropertyAnimation(
            time, property, start, dest, animation_direction,
            [  // Capture this by reference
                this,
                // these properties by copy
                time, start, dest, animation_direction,
                // Reference to the property by reference
                &property,
                // Move endAction inside the inner lambda
                endAction = std::move(endAction)]() {
                if (endAction)
                {
                    endAction();
                }
                addCircledPropertyAnimation(
                    time, property, start, dest,
                    (animation_direction == AnimationDirection::Forward)
                        ? AnimationDirection::Backward
                        : AnimationDirection::Forward,
                    std::move(endAction));
            });
    }

private:
    class AnimationComponentPrivate;
    htps::uptr<AnimationComponentPrivate> p_;
};
}  // namespace haf::anim

#endif
