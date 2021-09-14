#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/property_animation_data.hpp>
#include <haf/include/animation/animation_builder.hpp>
#include <haf/include/time/timer.hpp>

namespace haf::scene
{
    class SceneNode;
}

namespace haf::anim
{
/**
 * @brief Class to build a property animation
 *
 * @tparam T Type of the property to animate
 * @tparam Tag Type tag of the property to animate
 */
template <typename Tag, typename SceneNodeType>
class PropertyAnimationBuilder
{
private:
    AnimationBuilder base_animation_builder_;

public:
    PropertyAnimationBuilder& duration(time::TimePoint duration)
    {
        base_animation_builder_.duration(std::move(duration));
        return *this;
    }

    PropertyAnimationBuilder& endAction(ActionFunc end_action)
    {
        base_animation_builder_.endAction(std::move(end_action));
        return *this;
    }

    PropertyAnimationBuilder& animationDirection(
        AnimationDirection animation_direction)
    {
        base_animation_builder_.animationDirection(
            std::move(animation_direction));
        return *this;
    }

    PropertyAnimationBuilder& timer(htps::uptr<time::Timer> timer)
    {
        base_animation_builder_.timer(std::move(timer));
        return *this;
    }

    PropertyAnimationBuilder& times(htps::u32 times)
    {
        base_animation_builder_.times(std::move(times));
        return *this;
    }

    PropertyAnimationBuilder& continuous()
    {
        base_animation_builder_.continuous();
        return *this;
    }

    PropertyAnimationBuilder& switchAnimation(bool const value)
    {
        base_animation_builder_.switchAnimation(std::move(value));
        return *this;
    }

    PropertyAnimationBuilder& startValue(Tag::value_type start_value)
    {
        data_.startValue_ = std::move(start_value);
        return *this;
    }

    PropertyAnimationBuilder& endValue(Tag::value_type end_value)
    {
        data_.endValue_ = std::move(end_value);
        return *this;
    }

    PropertyAnimationBuilder& node(htps::rptr<SceneNodeType> node)
    {
        data_.scene_node_ = std::move(node);
        return *this;
    }

    PropertyAnimationBuilder& endActionType(AnimationEndAction action)
    {
        data_.animation_end_action_ = std::move(action);
        switch (data_.animation_end_action_)
        {
            case AnimationEndAction::PerformUserAction:
            {

            }
            break;
            case AnimationEndAction::RemoveAnimatedNode:
            {
                
            }
            break;
        }
        return *this;
    }

    PropertyAnimationData<Tag, SceneNodeType> extractData() noexcept
    {
        return std::move(data_);
    }

    void setData(PropertyAnimationData<Tag, SceneNodeType>&& data) noexcept
    {
        data_ = std::move(data);
    }

    AnimationData extractBaseData() noexcept
    {
        return std::move(base_animation_builder_.extractData());
    }

    void setBaseData(AnimationData&& animation_data) noexcept
    {
        base_animation_builder_.setData(std::move(animation_data));
    }

private:
    PropertyAnimationData<Tag, SceneNodeType> data_;
};

}  // namespace haf::anim

#endif
