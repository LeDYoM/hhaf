#ifndef ZOPER_TOKENZONES_INCLUDE_HPP
#define ZOPER_TOKENZONES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/rect.hpp>

#include "direction.hpp"

namespace zoper
{
using namespace haf;
constexpr htps::size_type NumWays(4);

struct TokenZones
{
    enum class BoardBackgroundType
    {
        Nothing = 0U,
        Center  = 1U
    };

    struct TokenZone
    {
        fmath::vector2dst zone_start;
        Direction direction;
        htps::size_type size;
    };

    constexpr static fmath::vector2dst size{18U, 12U};
    constexpr static fmath::Rectst centerRect{7U, 4U, 4U, 4U};

    constexpr static TokenZone tokenZones[NumWays] = {
        // From left to right
        TokenZone{fmath::vector2dst{0U, centerRect.top},
                  Direction::DirectionData::Right, centerRect.size().y},
        // From top to bottom
        TokenZone{fmath::vector2dst{centerRect.left, 0U},
                  Direction::DirectionData::Down, centerRect.size().x},
        // From right to left
        TokenZone{fmath::vector2dst{size.x - 1U, centerRect.top},
                  Direction::DirectionData::Left, centerRect.size().y},
        // From bottom to top
        TokenZone{fmath::vector2dst{centerRect.left, size.y - 1},
                  Direction::DirectionData::Up, centerRect.size().x}};

    static bool pointInCenter(const fmath::vector2dst& position)
    {
        return TokenZones::centerRect.inside(position);
    }

    template <typename T>
    static BoardBackgroundType toBoardBackgroundType(const T data) noexcept
    {
        return static_cast<BoardBackgroundType>(data);
    }

    constexpr static fmath::vector2dst displaceFactor(
        const Direction direction) noexcept
    {
        return fmath::vector2dst{(direction.isHorizontal() ? 0U : 1U),
                                 (direction.isHorizontal() ? 1U : 0U)};
    }

    static fmath::vector2dst displacedStartPoint(
        const TokenZone& token_zone,
        const htps::size_type displacement)
    {
        // Prepare the position for the new token
        return token_zone.zone_start +
            (displaceFactor(token_zone.direction) * displacement);
    }

    static fmath::vector2dst nearest_point_to_center(
        const TokenZone& token_zone,
        const fmath::vector2dst& start_point)
    {
        auto point{start_point};
        while (!pointInCenter(point))
        {
            point = token_zone.direction.negate().applyToVector(point);
        }

        return point;
    }
};
}  // namespace zoper

#endif
