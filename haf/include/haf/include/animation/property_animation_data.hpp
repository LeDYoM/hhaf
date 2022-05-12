HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/property_group.hpp>
#include <haf/include/animation/animation_data.hpp>

namespace haf::anim
{
template <typename T>
struct SceneNodeType : htps::BasicPropertyBase<htps::rptr<T>>
{};

template <typename PropertyTag>
struct StartValue : htps::BasicPropertyBase<typename PropertyTag::value_type>
{};

template <typename PropertyTag>
struct EndValue : htps::BasicPropertyBase<typename PropertyTag::value_type>
{};

template <typename PropertyTag, typename SceneNodeT>
using PropertyAnimationPropertiesSingle =
    htps::PropertyGroup<SceneNodeType<SceneNodeT>,
                        StartValue<PropertyTag>,
                        EndValue<PropertyTag>>;

template <typename PropertyTag, typename SceneNodeT>
using PropertyAnimationData = htps::PropertyGroupMixin<
    AnimationProperties,
    PropertyAnimationPropertiesSingle<PropertyTag, SceneNodeT>>;
}  // namespace haf::anim

#endif
