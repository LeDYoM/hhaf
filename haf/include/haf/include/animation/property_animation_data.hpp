HAF_PRAGMA_ONCE
#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation_data.hpp>
#include <haf/include/animation/delta_property.hpp>

namespace haf::anim
{
struct PropertyAnimationData : AnimationProperties
{
    htps::uptr<IDeltaProperty> delta_property;
};
}  // namespace haf::anim

#endif
