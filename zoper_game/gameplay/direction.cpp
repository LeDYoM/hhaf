#include "direction.hpp"
#include <hlog/include/hlog.hpp>

namespace zoper
{
Direction Direction::negate() const noexcept
{
    switch (data)
    {
        case DirectionData::Left:
            return DirectionData::Right;
        case DirectionData::Right:
            return DirectionData::Left;
        case DirectionData::Up:
            return DirectionData::Down;
        case DirectionData::Down:
            return DirectionData::Up;
        case DirectionData::Invalid:
        default:
            haf::DisplayLog::error("Invalid direction. Cannot convert");
    }
    return DirectionData::Invalid;
}

htps::vector2dst Direction::applyToVector(htps::vector2dst const& v,
                                          htps::u32 const scale) const noexcept
{
    htps::vector2ds32 const dv{directionVector(scale)};
    return {v.x + dv.x, v.y + dv.y};
}

htps::vector2ds32 Direction::directionVector(
    const htps::s32 scale) const noexcept
{
    switch (data)
    {
        case DirectionData::Left:
            return {-scale, 0};
        case DirectionData::Right:
            return {scale, 0};
        case DirectionData::Up:
            return {0, -scale};
        case DirectionData::Down:
            return {0, scale};
        case DirectionData::Invalid:
        default:
            haf::DisplayLog::error("Invalid direction. Cannot convert");
    }
    return {};
}

htps::vector2ds32 Direction::negatedDirectionVector(
    const htps::u32 scale) const noexcept
{
    return directionVector(scale) * -1;
}

htps::f32 Direction::angle() const noexcept
{
    switch (data)
    {
        case DirectionData::Left:
            return 180.F;
        case DirectionData::Right:
            return 0.F;
        case DirectionData::Up:
            return 270.F;
        case DirectionData::Down:
            return 90.F;
        case DirectionData::Invalid:
        default:
            haf::DisplayLog::error("Invalid direction. Cannot convert");
    }
    return 0.f;
}

Direction fromPositions(htps::vector2dst const& origin,
                        htps::vector2dst const& dest)
{
    htps::vector2ds32 const delta{static_cast<htps::vector2ds32>(dest) -
                                  static_cast<htps::vector2ds32>(origin)};
    if ((delta.x != 0 && delta.y != 0) || (delta.x == 0 && delta.y == 0))
    {
        haf::DisplayLog::error("Invalid vector diference. Cannot convert");
        return Direction::DirectionData::Invalid;
    }
    else if (delta.x > 0)
    {
        return Direction::DirectionData::Right;
    }
    else if (delta.x < 0)
    {
        return Direction::DirectionData::Left;
    }
    else if (delta.y > 0)
    {
        return Direction::DirectionData::Down;
    }
    else if (delta.y < 0)
    {
        return Direction::DirectionData::Up;
    }
    else
    {
        haf::DisplayLog::error("Invalid vector diference. Cannot convert");
        return Direction::DirectionData::Invalid;
    }
}

}  // namespace zoper
