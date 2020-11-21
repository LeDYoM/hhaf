#pragma once

#ifndef HAF_SCENE_IPROPERTY_ANIMATION_INCLUDE_HPP
#define HAF_SCENE_IPROPERTY_ANIMATION_INCLUDE_HPP

#include <haf/time/include/timepoint.hpp>
#include <haf/time/include/timeview.hpp>
#include <haf/time/include/timer.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>
#include <haf/scene_components/include/animation.hpp>
#include <haf/scene_components/include/animabletypes.hpp>

namespace haf::scene
{

/**
 * @brief Class representing an animation of a property. It uses functionality
 * from @b Animation to do that.
 *
 * @tparam T Type of the property to animate
 * @tparam AT Animable type corresponding to T
 */
template <typename T,
          typename PropertyTag = mtps::DummyTag,
          typename AT          = typename AnimableType<T>::type>
class IPropertyAnimation : public Animation
{
public:
    /**
     * @brief Construct a new IPropertyAnimation object
     *
     * @param timer Timer to be used to control the animation
     * @param duration Duration of the animation
     * @param prop Reference to an IProperty<T> to use
     * @param start Start value for the property
     * @param end End value for the property
     * @param animation_direction Direction to where the delta will go
     * @param endAction Functor with an action to perform when the animation
     *  is completed
     */
    IPropertyAnimation(mtps::uptr<time::Timer> timer,
                       time::TimePoint duration,
                       mtps::IProperty<T, PropertyTag>& prop,
                       T start,
                       T end,
                       Animation::AnimationDirection animation_direction,
                       ActionFunc endAction = {}) :
        Animation{std::move(timer), std::move(duration),
                  std::move(animation_direction), std::move(endAction)},
        property_{prop},
        startValue_{std::move(start)},
        endValue_{std::move(end)},
        deltaValue_{static_cast<AT>(AT{endValue_} - AT{startValue_})}
    {}

    virtual bool animate() override
    {
        const bool bResult{Animation::animate()};
        property_.set(AT{startValue_ + (deltaValue_ * delta())});
        return bResult;
    }

private:
    mtps::IProperty<T, PropertyTag>& property_;
    const T startValue_;
    const T endValue_;
    const AT deltaValue_{};
};
}  // namespace haf::scene

#endif
