#pragma once

#ifndef ZOPER_TOKENZONES_INCLUDE_HPP
#define ZOPER_TOKENZONES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

#include "direction.hpp"

namespace zoper
{
using namespace lib;
constexpr size_type NumWays(4);

struct TokenZones
{
    struct TokenZone
    {
        vector2dst zone_start;
        Direction direction;
        size_type size;
    };

    constexpr static vector2dst size{18, 12};
    constexpr static Rectst centerRect{7, 4, 4, 4};

    constexpr static TokenZone tokenZones[NumWays] =
        {
            // From left to right
            TokenZone{
                vector2dst{ 0U, centerRect.top },
                Direction::DirectionData::Right,
                centerRect.size().y},
            // From top to bottom
            TokenZone{
                vector2dst{ centerRect.left, 0U },
                Direction::DirectionData::Down,
                centerRect.size().x},
            // From right to left
            TokenZone{
                vector2dst{size.x - 1U, centerRect.top},
                Direction::DirectionData::Left,
                centerRect.size().y},
            // From bottom to top
            TokenZone{
                vector2dst{centerRect.left, size.y - 1},
                Direction::DirectionData::Up,
                centerRect.size().x}};

    static bool pointInCenter(const vector2dst &position)
    {
        return TokenZones::centerRect.inside(position);
    }

    constexpr static vector2dst displaceFactor(const Direction direction) noexcept
    {
        return vector2dst{
            (direction.isHorizontal() ? 0U : 1U),
            (direction.isHorizontal() ? 1U : 0U)};
    }

    static vector2dst displacedStartPoint(const TokenZone &token_zone,
                                          const size_type displacement)
    {
        // Prepare the position for the new token
        return token_zone.zone_start +
                           (displaceFactor(token_zone.direction) * displacement);
    }

    static vector2dst nearest_point_to_center(
        const TokenZone &token_zone,
        const vector2dst &start_point)
    {
        auto point{start_point};
        while (!pointInCenter(point))
        {
            point = token_zone.direction.negate().applyToVector(point);
        }

        return point;
    }
};
} // namespace zoper

#endif
