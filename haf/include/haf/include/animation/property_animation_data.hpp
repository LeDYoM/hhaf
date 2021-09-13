#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/animation/animation_data.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::anim
{
template <typename PropertyTag, typename SceneNodeType>
class PropertyAnimationData
{
public:
    htps::rptr<SceneNodeType> scene_node_{nullptr};
    typename PropertyTag::value_type startValue_;
    typename PropertyTag::value_type endValue_;
};

}  // namespace haf::anim

#endif
