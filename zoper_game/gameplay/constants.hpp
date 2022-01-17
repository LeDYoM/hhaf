#ifndef ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__
#define ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

namespace zoper::gameplay::constants
{
constexpr htps::u32 MillisAnimationPointsToScore = 600U;
constexpr htps::vector2df EndPositionPointsToScore =
    htps::vector2df{450.0F, 100.0F};

constexpr htps::u32 MillisAnimationLaunchPlayerStep = 125U;
}  // namespace zoper::gameplay::constants

#endif
