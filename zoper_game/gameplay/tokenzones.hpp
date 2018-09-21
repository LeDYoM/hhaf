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
            Rectst zone;
            Direction direction;
            size_type size;
        };

        constexpr static vector2dst size{ 18,12 };
        constexpr static Rectst centerRect{ 7,4,4,4 };

        constexpr static TokenZone tokenZones[NumWays] =
        {
            // From left to right
            TokenZone
            {
                Rectst{ 0,centerRect.top,centerRect.left - 1, centerRect.bottom() - 1 },
                Direction::DirectionData::Right,
                centerRect.size().y
            },
            // From top to bottom
            TokenZone
            {
                Rectst{ centerRect.left , 0, centerRect.right() - 1, centerRect.top - 1 },
                Direction::DirectionData::Down,
                centerRect.size().x
            },
            // From right to left
            TokenZone
            {
                Rectst{ size.x - 1 , centerRect.top,  centerRect.right(), centerRect.bottom() - 1 },
                Direction::DirectionData::Left,
                centerRect.size().y
            },
            // From bottom to top
            TokenZone
            {
                Rectst{ centerRect.left , size.y - 1, centerRect.right() - 1, centerRect.bottom() - 1 },
                Direction::DirectionData::Up,
                centerRect.size().x
            }
        };

        static bool pointInCenter(const vector2dst &position)
        {
            return TokenZones::centerRect.inside(position);
        }
    };
}

#endif
