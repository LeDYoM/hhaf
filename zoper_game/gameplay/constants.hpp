#ifndef ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__
#define ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>

namespace zoper::gameplay::constants
{
constexpr htps::u32 MillisAnimationPointsToScore = 600U;
constexpr fmath::vector2df EndPositionPointsToScore =
    fmath::vector2df{-0.275F, -0.4F};

constexpr htps::u32 MillisAnimationLaunchPlayerStep = 125U;
}  // namespace zoper::gameplay::constants

#endif
