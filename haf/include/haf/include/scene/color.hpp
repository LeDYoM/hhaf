HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_COLOR_INCLUDE_HPP
#define HAF_SCENE_COLOR_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/core/math_types.hpp>

namespace haf::scene::colors
{
using Color = core::vector4df;
static constexpr Color const White{OneF32, OneF32, OneF32, OneF32};
static constexpr Color const Black{ZeroF32, ZeroF32, ZeroF32, OneF32};
static constexpr Color const Grayk{0.25F, 0.25F, 0.25F, OneF32};
static constexpr Color const Red{OneF32, ZeroF32, ZeroF32, OneF32};
static constexpr Color const DarkRed{0.25F, ZeroF32, ZeroF32, OneF32};
static constexpr Color const Green{ZeroF32, OneF32, ZeroF32, OneF32};
static constexpr Color const DarkGreen{ZeroF32, 0.25F, ZeroF32, OneF32};
static constexpr Color const Blue{ZeroF32, ZeroF32, OneF32, OneF32};
static constexpr Color const DarkBlue{ZeroF32, ZeroF32, 0.25F, OneF32};
static constexpr Color const Yellow{OneF32, OneF32, ZeroF32, OneF32};
static constexpr Color const DarkYellow{0.25F, 0.25F, ZeroF32, OneF32};
static constexpr Color const Magenta{OneF32, ZeroF32, OneF32, OneF32};
static constexpr Color const DarkMagenta{0.25F, ZeroF32, 0.25F, OneF32};
static constexpr Color const Cyan{ZeroF32, OneF32, OneF32, OneF32};
static constexpr Color const DarkCyan{ZeroF32, 0.25F, 0.25F, OneF32};
static constexpr Color const Transparent{ZeroF32, ZeroF32, ZeroF32, ZeroF32};


}  // namespace haf::scene::colors

#endif
