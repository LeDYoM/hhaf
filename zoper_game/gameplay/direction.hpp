#pragma once

#ifndef ZOPER_DIRECTION_INCLUDE_HPP
#define ZOPER_DIRECTION_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <haf/include/liblog.hpp>

namespace zoper
{

class Direction
{
public:
    enum class DirectionData :  mtps::u8
    {
        Left = 0,
        Right = 1,
        Up = 2,
        Down = 3,
        Invalid = 4
    };
    static constexpr  mtps::u8 Total = static_cast< mtps::u8>(DirectionData::Invalid);

    constexpr Direction(DirectionData d) noexcept : data{d} {}
    constexpr Direction() noexcept : Direction{DirectionData::Up} {}
    constexpr Direction( mtps::u8 d) noexcept : Direction{static_cast<DirectionData>(d)} {}
    constexpr Direction(const Direction &other) noexcept = default;
    constexpr Direction &operator=(const Direction &other) noexcept = default;
    constexpr Direction(Direction &&other) noexcept = default;
    constexpr Direction &operator=(Direction &&other) noexcept = default;

    constexpr operator  mtps::u8() const noexcept { return static_cast< mtps::u8>(data); }

    constexpr DirectionData value() const noexcept { return data; }
    constexpr bool isValid() const noexcept { return data < DirectionData::Invalid; }

    constexpr bool isHorizontal() const noexcept { return data == DirectionData::Left || data == DirectionData::Right; }
    constexpr bool isVertical() const noexcept { return data == DirectionData::Up || data == DirectionData::Down; }

    constexpr Direction negate() const noexcept
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

    constexpr mtps::vector2dst applyToVector(const mtps::vector2dst &v, const mtps::u32 scale = 1U) const noexcept
    {
        const mtps::vector2ds32 dv{directionVector(scale)};
        return {v.x + dv.x, v.y + dv.y};
    }

    constexpr mtps::vector2ds32 directionVector(const mtps::s32 scale = 1) const noexcept
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

    constexpr mtps::vector2ds32 negatedDirectionVector(const mtps::u32 scale = 1U) const noexcept
    {
        return directionVector(scale) * -1;
    }

    constexpr mtps::f32 angle() const noexcept
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

private:
    DirectionData data;
};
} // namespace zoper

#endif
