HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <haf/include/animation/animation_data.hpp>
#include <haf/include/animation/delta_property.hpp>
import htypes;

namespace haf::anim
{
struct PropertyAnimationData : AnimationProperties
{
    htps::uptr<IDeltaProperty> delta_property;
};
}  // namespace haf::anim

#endif
