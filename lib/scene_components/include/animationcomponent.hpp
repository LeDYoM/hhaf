#pragma once

#ifndef HAF_ANIMATION_COMPONENT_INCLUDE_HPP
#define HAF_ANIMATION_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/icomponent.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/scene_components/include/animation.hpp>
#include <lib/scene_components/include/ipropertyanimation.hpp>

namespace haf::scene
{

class AnimationComponent : public IComponent
{
public:
    AnimationComponent();

    virtual void update() override;

    /**
     * @brief Add an already created animation to the list of animations.
     */
    void addAnimation(mtps::uptr<Animation>);

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
    template <typename PropertyType>
    void addPropertyAnimation(
        time::TimePoint time, mtps::IProperty<PropertyType> &property,
        PropertyType start, PropertyType dest,
        Animation::AnimationDirection animation_direction =
            Animation::AnimationDirection::Forward,
        Animation::ActionFunc endAction = {})
    {
        addAnimation(mtps::muptr<IPropertyAnimation<PropertyType>>(
            attachedNode()->dataWrapper<time::Timer>(),
            std::move(time), std::move(property), std::move(start),
            std::move(dest), std::move(animation_direction),
            std::move(endAction)));
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
    template <typename PropertyType>
    void addRepeatedPropertyAnimation(
        time::TimePoint time, mtps::IProperty<PropertyType> &property,
        PropertyType start, PropertyType dest,
        Animation::AnimationDirection animation_direction =
            Animation::AnimationDirection::Forward,
        Animation::ActionFunc endAction = {})
    {
        addPropertyAnimation(
            time, property, start, dest, animation_direction,
            [ // Capture this by reference
                this,
                // these properties by copy
                time, start, dest, animation_direction
                                       // Reference to the property by reference
                                       &property = property,
                // Move endAction inside the inner lambda
                endAction = std::move(endAction)]() {
                if (endAction)
                {
                    endAction();
                }
                addRepeatedPropertyAnimation(
                    time, property, start, dest, animation_direction,
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
    template <typename PropertyType>
    void addCircledPropertyAnimation(
        time::TimePoint time, mtps::IProperty<PropertyType> &property,
        PropertyType start, PropertyType dest,
        Animation::AnimationDirection animation_direction =
            Animation::AnimationDirection::Forward,
        Animation::ActionFunc endAction = {})
    {
        addPropertyAnimation(
            time, property, start, dest, animation_direction,
            [ // Capture this by reference
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
                    (animation_direction ==
                     Animation::AnimationDirection::Forward)
                        ? Animation::AnimationDirection::Backward
                        : Animation::AnimationDirection::Forward,
                    std::move(endAction));
            });
    }

private:
    class AnimationComponentPrivate;
    mtps::uptr<AnimationComponentPrivate> p_;
};
} // namespace haf::scene

#endif
