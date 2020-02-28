#pragma once

#ifndef LIB_SCENE_IPROPERTY_ANIMATION_INCLUDE_HPP
#define LIB_SCENE_IANIMATION_INCLUDE_HPP

#include <lib/time/include/timepoint.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/time/include/timer.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene_components/include/animation.hpp>

namespace lib::scene
{

/**
 * @brief Class representing an animation. The animation will be updated when
 *  the animate() method is call.
 * 
 * @tparam T Type of the property to animate.
 */
template <typename T>
class IPropertyAnimation : public IAnimation
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
    IPropertyAnimation(uptr<time::Timer> timer, time::TimePoint duration,
                       IProperty<T> &prop, T start, T end,
                       IAnimation::AnimationDirection animation_direction,
                       ActionFunc endAction = {})
        : IAnimation{std::move(timer), std::move(duration),
                     std::move(animation_direction), std::move(endAction)},
          property_{prop}, startValue_{std::move(start)},
          endValue_{std::move(end)},
          deltaValue_{endValue_ - startValue_}
    {
    }

    virtual bool animate() override
    {
        const bool bResult{IAnimation::animate()};
        property_.set(T{startValue_ + (deltaValue_ * delta())});
        return bResult;
    }

protected:
    IProperty<T> &property_;
    T startValue_;
    T endValue_;
    T deltaValue_;
};
} // namespace lib::scene

#endif
