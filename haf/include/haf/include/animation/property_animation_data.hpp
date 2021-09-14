#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation_data.hpp>

namespace haf::anim
{
enum class AnimationEndAction
{
    PerformUserAction  = 0U,
    RemoveAnimatedNode = 1U
};

template <typename PropertyTag, typename SceneNodeType>
class PropertyAnimationData
{
public:
    htps::rptr<SceneNodeType> scene_node_{nullptr};
    typename PropertyTag::value_type startValue_;
    typename PropertyTag::value_type endValue_;
    AnimationEndAction animation_end_action_{
        AnimationEndAction::PerformUserAction};  //< Type of action to perform
                                                 //< when animation ends
};

}  // namespace haf::anim

#endif
