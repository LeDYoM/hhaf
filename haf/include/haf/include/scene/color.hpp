HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_COLOR_INCLUDE_HPP
#define HAF_SCENE_COLOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/color_imp.hpp>

namespace haf::scene
{
extern template struct ColorImp<htps::u8>;
using Color = ColorImp<htps::u8>;

namespace colors
{
static const Color Black{Color::value_min, Color::value_min, Color::value_min};
static const Color White{Color::value_max, Color::value_max, Color::value_max};
static const Color Red{Color::value_max, Color::value_min, Color::value_min};
static const Color Green{Color::value_min, Color::value_max, Color::value_min};
static const Color Blue{Color::value_min, Color::value_min, Color::value_max};
static const Color Yellow{Color::value_max, Color::value_max, Color::value_min};
static const Color Magenta{Color::value_max, Color::value_min,
                           Color::value_max};
static const Color Cyan{Color::value_min, Color::value_max, Color::value_max};
static const Color Transparent{Color::value_min, Color::value_min,
                               Color::value_min, Color::value_min};
}  // namespace colors

}  // namespace haf::scene

#endif
