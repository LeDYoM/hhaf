#include "direction.hpp"
#include <hlog/include/hlog.hpp>

using namespace haf;

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
            DisplayLog::error("Invalid direction. Cannot convert");
    }
    return DirectionData::Invalid;
}

fmath::vector2dst Direction::applyToVector(fmath::vector2dst const& v,
                                           htps::u32 const scale) const noexcept
{
    fmath::vector2ds32 const dv{directionVector(scale)};
    return {v.x + dv.x, v.y + dv.y};
}

fmath::vector2ds32 Direction::directionVector(
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
            DisplayLog::error("Invalid direction. Cannot convert");
    }
    return {};
}

fmath::vector2ds32 Direction::negatedDirectionVector(
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
            DisplayLog::error("Invalid direction. Cannot convert");
    }
    return 0.f;
}

Direction fromPositions(fmath::vector2dst const& origin,
                        fmath::vector2dst const& dest)
{
    fmath::vector2ds32 const delta{static_cast<fmath::vector2ds32>(dest) -
                                   static_cast<fmath::vector2ds32>(origin)};
    if ((delta.x != 0 && delta.y != 0) || (delta.x == 0 && delta.y == 0))
    {
        DisplayLog::error("Invalid vector diference. Cannot convert");
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
        DisplayLog::error("Invalid vector diference. Cannot convert");
        return Direction::DirectionData::Invalid;
    }
}

}  // namespace zoper
