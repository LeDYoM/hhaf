HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_COLOR_INCLUDE_HPP
#define HAF_SCENE_COLOR_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <facil_math/include/math_types.hpp>

namespace haf::scene::colors
{
using Color = fmath::vector4df;
static constexpr auto const Full{fmath::OneF32};
static constexpr auto const Empty{fmath::ZeroF32};
static constexpr auto const OneForth{0.25F};

static constexpr Color const White{Full, Full, Full, Full};
static constexpr Color const Black{Empty, Empty, Empty, Full};
static constexpr Color const Grayk{OneForth, OneForth, OneForth, Full};
static constexpr Color const Red{Full, Empty, Empty, Full};
static constexpr Color const DarkRed{OneForth, Empty, Empty, Full};
static constexpr Color const Green{Empty, Full, Empty, Full};
static constexpr Color const DarkGreen{Empty, OneForth, Empty, Full};
static constexpr Color const Blue{Empty, Empty, Full, Full};
static constexpr Color const DarkBlue{Empty, Empty, OneForth, Full};
static constexpr Color const Yellow{Full, Full, Empty, Full};
static constexpr Color const DarkYellow{OneForth, OneForth, Empty, Full};
static constexpr Color const Magenta{Full, Empty, Full, Full};
static constexpr Color const DarkMagenta{OneForth, Empty, OneForth, Full};
static constexpr Color const Cyan{Empty, Full, Full, Full};
static constexpr Color const DarkCyan{Empty, OneForth, OneForth, Full};
static constexpr Color const Transparent{Empty, Empty, Empty, Empty};

}  // namespace haf::scene::colors

#endif
