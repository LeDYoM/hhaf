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
template <typename T, typename PropertyTag, typename SceneNodeType = scene::SceneNode>
class PropertyAnimationData
{
public:
    htps::IProperty<T, PropertyTag>* property_;
    htps::rptr<SceneNodeType> scene_node_{nullptr};
    T startValue_;
    T endValue_;
};

}  // namespace haf::anim

#endif
