#pragma once

#ifndef LIB_SCENE_IANIMATION_INCLUDE_HPP
#define LIB_SCENE_IANIMATION_INCLUDE_HPP

#include <lib/time/include/timepoint.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/time/include/timer.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>

namespace lib::scene
{
class Animation
{
public:
    using ActionFunc = function<void()>;
    enum class AnimationDirection : u8
    {
        Forward = 0U,
        Backward
    };

    /**
     * @brief Construct a new Animation object
     * 
     * @param timer @b Timer to use to animate
     * @param duration @b time::TimePoint containing the time the animation is
     *  going to last
     * @param animation_direction @b AnimationDirection Direction of the
     *  animation
     * @param endAction Functor containing an action to perform when the
     *  animation finishes
     */
    Animation(uptr<time::Timer> timer, time::TimePoint duration,
               const AnimationDirection animation_direction,
               ActionFunc endAction = {}) noexcept;

    /**
     * @brief Performs one step on the animation
     * 
     * @return true If the animation should continue
     * @return false The animation should finish
     */
    virtual bool animate();

    /**
     * @brief Destroy the Animation object
     */
    virtual ~Animation();

    /**
     * @brief Execute an action at the end of the animation
     */
    void executeEndAction();

protected:
    f32 delta() const noexcept { return delta_; }

private:
    uptr<time::Timer> timer_;
    time::TimePoint m_duration;
    time::TimePoint m_currentTime;
    ActionFunc m_endAction;
    AnimationDirection animation_direction_;
    f32 raw_delta_;
    f32 delta_;

private:
    f32 postProcessDelta(const f32 delta);
};

} // namespace lib::scene

#endif
