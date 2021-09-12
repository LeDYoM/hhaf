#ifndef HAF_ANIM_IPROPERTY_ANIMATION_INCLUDE_HPP
#define HAF_ANIM_IPROPERTY_ANIMATION_INCLUDE_HPP

#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timeview.hpp>
#include <haf/include/time/timer.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/animation/animation.hpp>
#include <haf/include/animation/animabletypes.hpp>
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
 *
 * @tparam T Type of the property to animate
 * @tparam PropertyTag Tag attached to the property
 * @tparam AT Animable type corresponding to T
 */
template <typename T,
          typename PropertyTag,
          typename AT = typename AnimableType<T>::type,
        typename SceneNodeType = scene::SceneNode>
class PropertyAnimation : public Animation
{
public:
    /**
     * @brief Construct a new PropertyAnimation object
     *
     * @param animation_data Data for the animation
     * @param property_animation_data Data for the property animation
     */
    PropertyAnimation(
        AnimationData&& animation_data,
        PropertyAnimationData<T, PropertyTag, SceneNodeType>&& property_animation_data) :
        Animation{std::move(animation_data)},
        data_{std::move(property_animation_data)},
        deltaValue_{AT{data_.endValue_} - AT{data_.startValue_}}
    {}

    bool animate() override
    {
        // Get result from parent
        const bool bResult{Animation::animate()};
        (*(data_.property_))
            .set(AT{data_.startValue_ + (deltaValue_ * delta())});
        return bResult;
    }

private:
    PropertyAnimationData<T, PropertyTag, SceneNodeType> data_;
    const AT deltaValue_{};
};
}  // namespace haf::anim

#endif
