HTPS_PRAGMA_ONCE
#ifndef HAF_ANIM_ANIMABLETYPE_INCLUDE_HPP
#define HAF_ANIM_ANIMABLETYPE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::anim
{
template <typename PropertyType>
PropertyType interpolate(PropertyType const& begin,
                         PropertyType const& end,
                         htps::f32 const delta)
{
    return begin + ((end - begin) * delta);
}

template <>
inline scene::Color interpolate<scene::Color>(scene::Color const& begin,
                                              scene::Color const& end,
                                              htps::f32 const delta)
{
    using namespace htps;
    f32 my_r{interpolate(static_cast<f32>(begin.red()),
                         static_cast<f32>(end.red()), delta)};
    f32 my_g{interpolate(static_cast<f32>(begin.green()),
                         static_cast<f32>(end.green()), delta)};
    f32 my_b{interpolate(static_cast<f32>(begin.blue()),
                         static_cast<f32>(end.blue()), delta)};
    f32 my_a{interpolate(static_cast<f32>(begin.alpha()),
                         static_cast<f32>(end.alpha()), delta)};

    return scene::Color{static_cast<u8>(my_r), static_cast<u8>(my_g),
                        static_cast<u8>(my_b), static_cast<u8>(my_a)};
}

}  // namespace haf::anim

#endif
