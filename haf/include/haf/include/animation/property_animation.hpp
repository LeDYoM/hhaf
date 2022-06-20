HTPS_PRAGMA_ONCE
#ifndef HAF_ANIM_IPROPERTY_ANIMATION_INCLUDE_HPP
#define HAF_ANIM_IPROPERTY_ANIMATION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation.hpp>
#include <haf/include/animation/property_animation_data.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::anim
{
/**
 * @brief Class representing an animation of a property. It uses functionality
 * from @b Animation to do that.
*/
class PropertyAnimation : public Animation
{
    using BaseClass = Animation;

public:
    /**
     * @brief Construct a new PropertyAnimation object
     *
     * @param animation_data Data for the animation
     * @param property_animation_data Data for the property animation
     */
    PropertyAnimation(PropertyAnimationData&& property_animation_data);

    bool animate() override;

private:
    PropertyAnimationData data_;
};
}  // namespace haf::anim

#endif
