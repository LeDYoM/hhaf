#ifndef ZOPER_DIRECTION_INCLUDE_HPP
#define ZOPER_DIRECTION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>

namespace zoper
{
class Direction
{
    using DirectionDataUnderlying = htps::u8;

public:
    enum class DirectionData : DirectionDataUnderlying
    {
        Left    = 0U,
        Right   = 1U,
        Up      = 2U,
        Down    = 3U,
        Invalid = 4U,
    };
    static constexpr DirectionDataUnderlying Total =
        static_cast<DirectionDataUnderlying>(DirectionData::Invalid);

    constexpr Direction(DirectionData const d) noexcept : data{d} {}
    constexpr Direction() noexcept : Direction{DirectionData::Up} {}
    constexpr Direction(Direction const& other) noexcept = default;
    constexpr Direction& operator=(Direction const& other) noexcept = default;
    constexpr Direction(Direction&& other) noexcept                 = default;
    constexpr Direction& operator=(Direction&& other) noexcept = default;

    constexpr DirectionData value() const noexcept { return data; }
    constexpr bool operator==(Direction const& rhs) const noexcept
    {
        return data == rhs.data;
    }

    constexpr bool operator!=(Direction const& rhs) const noexcept
    {
        return data != rhs.data;
    }

    constexpr bool isValid() const noexcept
    {
        return data < DirectionData::Invalid;
    }

    constexpr bool isHorizontal() const noexcept
    {
        return data == DirectionData::Left || data == DirectionData::Right;
    }
    constexpr bool isVertical() const noexcept
    {
        return data == DirectionData::Up || data == DirectionData::Down;
    }

    Direction negate() const noexcept;

    fmath::vector2dst applyToVector(fmath::vector2dst const& v,
                                   htps::u32 const scale = 1U) const noexcept;

    fmath::vector2ds32 directionVector(const htps::s32 scale = 1) const noexcept;

    fmath::vector2ds32 negatedDirectionVector(
        const htps::u32 scale = 1U) const noexcept;

    htps::f32 angle() const noexcept;

private:
    DirectionData data;
};

Direction fromPositions(fmath::vector2dst const& origin,
                        fmath::vector2dst const& dest);
}  // namespace zoper

#endif
