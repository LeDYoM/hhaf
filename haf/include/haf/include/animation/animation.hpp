HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_IANIMATION_INCLUDE_HPP
#define HAF_ANIMATION_IANIMATION_INCLUDE_HPP

#include <haf/include/animation/animation_data.hpp>
#include <haf/include/animation/property_animation_data.hpp>

#include <haf/include/time/time_point.hpp>
#include <haf/include/time/time_view.hpp>
#include <haf/include/time/timer.hpp>

#include <htypes/include/types.hpp>
#include <haf/include/properties/iproperty.hpp>
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
    Animation(AnimationProperties&& animation_data) noexcept;

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
     * @brief Execute an action before starting to update the animation
     */
    void executeStartAction();

    /**
     * @brief Execute an action at the end of the animation if it is set
     */
    void executeEndAction();

protected:
    using AnimationDeltaType = htps::f32;
    AnimationDeltaType delta() const noexcept { return m_delta; }

private:
    AnimationProperties m_animation_data;
    AnimationDirection m_current_direction;
    time::TimePoint m_current_time;
    AnimationDeltaType m_raw_delta;
    AnimationDeltaType m_delta;
    bool m_end_reached;

    AnimationDeltaType postProcessDelta(AnimationDeltaType const delta);
};

}  // namespace haf::anim

#endif
