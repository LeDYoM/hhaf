HTPS_PRAGMA_ONCE
#ifndef HAF_ANIM_ANIMABLETYPE_INCLUDE_HPP
#define HAF_ANIM_ANIMABLETYPE_INCLUDE_HPP

import htypes;

namespace haf::anim
{
template <typename PropertyType>
PropertyType interpolate(PropertyType const& begin,
                         PropertyType const& end,
                         htps::f32 const delta)
{
    return begin + ((end - begin) * delta);
}

}  // namespace haf::anim

#endif
