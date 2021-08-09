#ifndef HAF_ANIMATION_IANIMATION_INCLUDE_HPP
#define HAF_ANIMATION_IANIMATION_INCLUDE_HPP

#include <haf/include/animation/animation_data.hpp>
#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timeview.hpp>
#include <haf/include/time/timer.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/function.hpp>

namespace haf::anim
{
/**
 * @brief Class representing an animation. The animation will be updated when
 *  the animate() method is called.
 */
class Animation
{
public:
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
    Animation(htps::uptr<time::Timer> timer,
              time::TimePoint duration,
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
    htps::f32 delta() const noexcept { return delta_; }

private:
    AnimationData animation_data_;
    time::TimePoint current_time_;
    htps::f32 raw_delta_;
    htps::f32 delta_;

    htps::f32 postProcessDelta(const htps::f32 delta);
};

}  // namespace haf::anim

#endif
