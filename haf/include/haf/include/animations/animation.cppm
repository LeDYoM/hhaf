export module haf:animation:animation;

import :animation_data;
import :property_animation_data;
import :property_animation_data;
import :time:timer;
import :time:time_point;
import :time:time_view;
import :properties:iproperty;
import htypes;

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
    explicit Animation(AnimationProperties&& animation_data) noexcept :
        animation_data_{htps::move(animation_data)},
        current_direction_{animation_data_.AnimationDirectionProperty()},
        current_time_{},
        raw_delta_{static_cast<AnimationDeltaType>(0.0)},
        delta_{postProcessDelta(raw_delta_)},
        end_reached_{false}
    {}

    /**
     * @brief Destroy the Animation object
     */
    virtual ~Animation() = default;

    /**
     * @brief Performs one step on the animation
     *
     * @return true If the animation should continue
     * @return false The animation should finish
     */
    virtual bool animate()
    {
        current_time_ = animation_data_.TimerProperty()->ellapsed();

        bool continue_animation{current_time_ <= animation_data_.Duration()};
        raw_delta_ = (continue_animation)
            ? (static_cast<decltype(raw_delta_)>(current_time_.milliseconds()) /
               animation_data_.Duration().milliseconds())
            : static_cast<AnimationDeltaType>(1.0);

        delta_       = postProcessDelta(raw_delta_);
        end_reached_ = !continue_animation;

        if (end_reached_)
        {
            // Should we stop animations?
            // Reduce the number of pending loops if animation type is not
            // infinite
            if (animation_data_.Times() != -1)
            {
                animation_data_.Times = animation_data_.Times() - 1;
            }
            continue_animation = animation_data_.Times() != 0;

            if (continue_animation)
            {
                if (animation_data_.Switch())
                {
                    current_direction_ =
                        ((current_direction_ == AnimationDirection::Forward)
                             ? AnimationDirection::Backward
                             : AnimationDirection::Forward);
                }
                animation_data_.TimerProperty()->restart();
            }
        }
        return continue_animation;
    }

    /**
     * @brief Execute an action at the end of the animation
     */
    void executeEndAction()
    {
        animation_data_.TimerProperty()->markToDelete();
        // If property containing the function wrapper contains a function, call
        // it
        if (animation_data_.ActionWhenFinished())
        {
            animation_data_.ActionWhenFinished()();
        }
    }

protected:
    using AnimationDeltaType = htps::f32;
    AnimationDeltaType delta() const noexcept { return delta_; }

private:
    AnimationProperties animation_data_;
    AnimationDirection current_direction_;
    time::TimePoint current_time_;
    AnimationDeltaType raw_delta_;
    AnimationDeltaType delta_;
    bool end_reached_;

    AnimationDeltaType postProcessDelta(AnimationDeltaType const delta)
    {
        switch (current_direction_)
        {
            default:
            case AnimationDirection::Forward:
                return delta;
                break;
            case AnimationDirection::Backward:
                return (static_cast<AnimationDeltaType>(1.0) - delta);
                break;
        }
    }
};

}  // namespace haf::anim
