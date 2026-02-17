export module haf:animations:animable_types;

import :core:types;

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
