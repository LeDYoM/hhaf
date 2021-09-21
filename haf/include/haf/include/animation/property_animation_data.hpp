#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/animation/animation_data.hpp>

namespace haf::anim
{
template <typename T>
struct SceneNodeType
{
    using value_type = types::rptr<T>;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

template <typename PropertyTag>
struct StartValue
{
    using value_type = typename PropertyTag::value_type;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

template <typename PropertyTag>
struct EndValue
{
    using value_type = typename PropertyTag::value_type;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

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
