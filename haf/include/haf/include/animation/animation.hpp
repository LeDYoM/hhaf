#ifndef HAF_ANIMATION_IANIMATION_INCLUDE_HPP
#define HAF_ANIMATION_IANIMATION_INCLUDE_HPP

#include <haf/include/animation/animation_data.hpp>
#include <haf/include/animation/animation_builder.hpp>
#include <haf/include/animation/property_animation_data.hpp>
#include <haf/include/animation/property_animation_builder.hpp>

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
     * @param animation_data Data for the animation
     * @see AnimationData
     */
    Animation(AnimationData&& animation_data) noexcept;

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
    using AnimationDeltaType = htps::f32;

    AnimationData animation_data_;
    AnimationDirection current_direction_;
    time::TimePoint current_time_;
    AnimationDeltaType raw_delta_;
    AnimationDeltaType delta_;
    bool end_reached_;

    AnimationDeltaType postProcessDelta(AnimationDeltaType const delta);
};

}  // namespace haf::anim

#endif
