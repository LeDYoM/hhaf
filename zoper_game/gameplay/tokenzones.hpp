#ifndef ZOPER_TOKENZONES_INCLUDE_HPP
#define ZOPER_TOKENZONES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

#include "direction.hpp"

namespace zoper
{
using namespace haf;
constexpr mtps::size_type NumWays(4);

struct TokenZones
{
    enum class BoardBackgroundType
    {
        Nothing = 0U,
        Center = 1U
    };

    struct TokenZone
    {
        mtps::vector2dst zone_start;
        Direction direction;
        mtps::size_type size;
    };

    constexpr static mtps::vector2dst size{18U, 12U};
    constexpr static mtps::Rectst centerRect{7U, 4U, 4U, 4U};

    constexpr static TokenZone tokenZones[NumWays] = {
        // From left to right
        TokenZone{mtps::vector2dst{0U, centerRect.top},
                  Direction::DirectionData::Right, centerRect.size().y},
        // From top to bottom
        TokenZone{mtps::vector2dst{centerRect.left, 0U},
                  Direction::DirectionData::Down, centerRect.size().x},
        // From right to left
        TokenZone{mtps::vector2dst{size.x - 1U, centerRect.top},
                  Direction::DirectionData::Left, centerRect.size().y},
        // From bottom to top
        TokenZone{mtps::vector2dst{centerRect.left, size.y - 1},
                  Direction::DirectionData::Up, centerRect.size().x}};

    static bool pointInCenter(const mtps::vector2dst& position)
    {
        return TokenZones::centerRect.inside(position);
    }

    template <typename T>
    static BoardBackgroundType toBoardBackgroundType(const T data) noexcept
    {
        return static_cast<BoardBackgroundType>(data);
    }

    constexpr static mtps::vector2dst displaceFactor(
        const Direction direction) noexcept
    {
        return mtps::vector2dst{(direction.isHorizontal() ? 0U : 1U),
                                (direction.isHorizontal() ? 1U : 0U)};
    }

    static mtps::vector2dst displacedStartPoint(
        const TokenZone& token_zone,
        const mtps::size_type displacement)
    {
        // Prepare the position for the new token
        return token_zone.zone_start +
            (displaceFactor(token_zone.direction) * displacement);
    }

    static mtps::vector2dst nearest_point_to_center(
        const TokenZone& token_zone,
        const mtps::vector2dst& start_point)
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
