#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/animation/animation_data.hpp>

namespace haf::anim
{
template <typename T>
struct SceneNodeType : BasicPropertyBase<types::rptr<T>> {};

template <typename PropertyTag>
struct StartValue : BasicPropertyBase<typename PropertyTag::value_type> {};

template <typename PropertyTag>
struct EndValue : BasicPropertyBase<typename PropertyTag::value_type> {};

template <typename PropertyTag, typename SceneNodeT>
using PropertyAnimationPropertiesSingle =
    types::PropertyGroup<SceneNodeType<SceneNodeT>,
                         StartValue<PropertyTag>,
                         EndValue<PropertyTag>>;

template <typename PropertyTag, typename SceneNodeT>
using PropertyAnimationData = htps::PropertyGroupMixin<
    AnimationProperties,
    PropertyAnimationPropertiesSingle<PropertyTag, SceneNodeT>>;
}  // namespace haf::anim

#endif
