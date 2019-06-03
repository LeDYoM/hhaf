#pragma once

#ifndef ZOPER_DIRECTION_INCLUDE_HPP__
#define ZOPER_DIRECTION_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <logger/include/log.hpp>

namespace zoper
{
	using namespace lib;

	class Direction
    {
    public:
        enum class DirectionData : u8
        {
            Left = 0,
            Right = 1,
            Up = 2,
            Down = 3,
            Invalid = 4
        };
        constexpr Direction(DirectionData d) : data{ d } {}
        constexpr Direction() : Direction{ DirectionData::Up } {}
        constexpr Direction(u8 d) : data{ static_cast<DirectionData>(d) } {}
        constexpr Direction(const Direction &other) = default;
        constexpr Direction &operator=(const Direction &other) = default;
        constexpr Direction(Direction &&other) = default;
        constexpr Direction &operator=(Direction &&other) = default;

        constexpr operator u8() const noexcept { return static_cast<u8>(data); }

        constexpr DirectionData value() const noexcept { return data; }
        constexpr bool isValid() const noexcept { return data < DirectionData::Invalid; }

        static constexpr u8 Total = static_cast<u8>(DirectionData::Invalid);

        constexpr bool isHorizontal() const noexcept { return data == DirectionData::Left || data == DirectionData::Right; }
		constexpr bool isVertical() const noexcept { return data == DirectionData::Up || data == DirectionData::Down; }

        constexpr  Direction negate() const noexcept {
            switch (data)
            {
            case DirectionData::Left:
                return DirectionData::Right;
                break;
            case DirectionData::Right:
                return DirectionData::Left;
                break;
            case DirectionData::Up:
                return DirectionData::Down;
                break;
            case DirectionData::Down:
                return DirectionData::Up;
                break;
            case DirectionData::Invalid:
            default:
                lib::log_debug_error("Invalid direction. Cannot convert");
            }
            return DirectionData::Invalid;
        }

        constexpr vector2dst applyToVector(const vector2dst &v, const u32 scale = 1) const noexcept
        {
            const vector2ds32 dv{ directionVector(scale) };
            return { v.x + dv.x, v.y + dv.y };
        }

        constexpr lib::vector2ds32 directionVector(const lib::s32 scale = 1) const noexcept
        {
            switch (data)
            {
            case DirectionData::Left:
                return { -scale, 0 };
                break;
            case DirectionData::Right:
                return { scale, 0 };
                break;
            case DirectionData::Up:
                return { 0, -scale };
                break;
            case DirectionData::Down:
                return { 0, scale };
                break;
            case DirectionData::Invalid:
            default:
                log_debug_error("Invalid direction. Cannot convert");
                return {};
            }
        }

        constexpr lib::vector2ds32 negatedDirectionVector(const lib::u32 scale = 1) const noexcept
        {
            return directionVector(scale) * - 1;
        }

        constexpr lib::f32 angle() const noexcept
        {
            switch (data)
            {
            case DirectionData::Left:
                return 180.F;
                break;
            case DirectionData::Right:
                return 0.F;
                break;
            case DirectionData::Up:
                return 270.F;
                break;
            case DirectionData::Down:
                return 90.F;
                break;
            case DirectionData::Invalid:
            default:
                lib::log_debug_error("Invalid direction. Cannot convert");
                return 0.f;
            }

        }

    private:
        DirectionData data;
    };
}

#endif
