export module haf:animations:property_animation_data;

import :animation_data;
import :delta_property;
import :core:types;

namespace haf::anim
{
struct PropertyAnimationData : AnimationProperties
{
    htps::uptr<IDeltaProperty> delta_property;
};
}  // namespace haf::anim
