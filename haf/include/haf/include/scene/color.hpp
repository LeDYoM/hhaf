HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_COLOR_INCLUDE_HPP
#define HAF_SCENE_COLOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <algorithm>
#include <limits>

#include <haf/include/animation/animable_types.hpp>

namespace haf::scene
{
namespace detail
{
template <typename value_type>
static constexpr value_type const value_max =
    std::numeric_limits<value_type>::max();

template <typename value_type>
static constexpr value_type const value_min =
    std::numeric_limits<value_type>::min();

template <typename Dest, typename Source>
constexpr Dest ensureLimits(Source const source) noexcept
{
    return static_cast<Dest>(
        std::min(static_cast<Source>(value_max<Dest>),
                 std::max(source, static_cast<Source>(value_min<Dest>))));
}

template <typename value_type>
constexpr htps::f32 normalize(value_type const v) noexcept
{
    return static_cast<htps::f32>(
        static_cast<htps::f32>(v) /
        static_cast<htps::f32>(value_max<value_type>));
}

template <typename value_type>
constexpr void denormalize(const htps::f32 v, value_type& d) noexcept
{
    d = static_cast<value_type>(v * value_max<value_type>);
}

}  // namespace detail

/**
 * @brief Class representing a color. The suffix helps to
 * create custom specializations with more meaningful names.
 * This class contains red, green, value and alpha values
 * representing a color in the (r,g,b,a) space.
 *
 * @tparam value_type Type to represent the interal data values.
 */
struct Color
{
    using value_type = htps::u8;

    /**
     * @brief Maximum value for each coordinate
     */
    static constexpr value_type value_max = detail::value_max<value_type>;

    /**
     * @brief Minimum value for each coordinate
     */
    static constexpr value_type value_min = detail::value_min<value_type>;

    /**
     * @brief Ensure that a value is between the required limits
     *
     * @tparam Source Type of the source value
     * @param source Source value of type Source
     * @return value_type Value of the type required for this Color
     */
    template <typename Source>
    static constexpr value_type ensureLimits(Source source) noexcept
    {
        return detail::ensureLimits<value_type, Source>(htps::move(source));
    }

    /**
     * @brief Static constant defining the value for opaque colors
     */
    static constexpr value_type Opaque = value_max;

    /**
     * @brief Static constant defining the value for transparent colors
     */
    static constexpr value_type Transparent = value_min;

    /**
     * @brief Default constructor. Sets color to black opaque
     */
    constexpr Color() noexcept :
        r{value_min}, g{value_min}, b{value_min}, a{value_max}
    {}

    /**
     * @brief Construct a Color object from four values
     * @param red Red component of the color
     * @param green Green component of the color
     * @param blue Blue component of the color
     * @param alpha Alpha component of the color (Defaulted to opaque)
     */
    constexpr Color(value_type const red,
                    value_type const green,
                    value_type const blue,
                    value_type const alpha = value_max) noexcept :
        r{red}, g{green}, b{blue}, a{alpha}
    {}

    constexpr Color(Color const&) noexcept = default;
    constexpr Color& operator=(Color const&) noexcept = default;
    constexpr Color(Color&&) noexcept                 = default;
    constexpr Color& operator=(Color&&) noexcept = default;

    /**
     * @brief Construct a Color object from another color, but with a
     * different alpha.
     * @param base_color The color that will give the r,g,b values
     * @param alpha The alpha value
     */
    constexpr Color(Color const& base_color, value_type const alpha) noexcept :
        r{base_color.r}, g{base_color.g}, b{base_color.b}, a{alpha}
    {}

    constexpr explicit Color(htps::u32 const color) noexcept :
        r{static_cast<value_type>((color & 0xFF000000) >> 24U)},
        g{static_cast<value_type>((color & 0x00FF0000) >> 16U)},
        b{static_cast<value_type>((color & 0x0000FF00) >> 8U)},
        a{static_cast<value_type>((color & 0x000000FF) >> 0U)}
    {}

    static constexpr Color fromFloats(htps::f32 const red,
                                         htps::f32 const green,
                                         htps::f32 const blue,
                                         htps::f32 const alpha = 1.0F) noexcept
    {
        return Color{static_cast<value_type>(red * value_max),
                     static_cast<value_type>(green * value_max),
                     static_cast<value_type>(blue * value_max),
                     static_cast<value_type>(alpha * value_max)};
    }

    /**
     * @brief Equality comparation with another Color of the same type
     *
     * @param rhs Right part of the comparison
     * @return The colors are equal
     * @return The colors are not equal
     */
    constexpr bool operator==(Color const& rhs) const noexcept
    {
        return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
    }

    /**
     * @brief Unequality comparation with another Color of the same type
     *
     * @param rhs Right part of the comparison
     * @return The colors are not equal
     * @return The colors are equal
     */
    constexpr bool operator!=(Color const& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    /**
     * @brief Substract two colors (They might be of different type). The result
     * is ensured to be a valid color of the source type
     *
     * @param rhs  Right hand side operand
     * @return Color with the resulting color
     */
    constexpr Color operator-(Color const& rhs) const noexcept
    {
        return Color{*this} -= rhs;
    }

    /**
     * @brief Multiply two colors (They might be of different type). The result
     * is ensured to be a valid color of the source type
     *
     * @param rhs  Right hand side operand
     * @return Color with the resulting color
     */
    constexpr Color operator*(Color const& rhs) const noexcept
    {
        return Color{*this} *= rhs;
    }

    constexpr Color& operator+=(Color const& right) noexcept
    {
        r = ensureLimits(r + right.r);
        g = ensureLimits(g + right.g);
        b = ensureLimits(b + right.b);
        a = ensureLimits(a + right.a);
        return *this;
    }

    constexpr Color& operator-=(Color const& right) noexcept
    {
        r = ensureLimits(static_cast<htps::s32>(r) - right.r);
        g = ensureLimits(static_cast<htps::s32>(g) - right.g);
        b = ensureLimits(static_cast<htps::s32>(b) - right.b);
        a = ensureLimits(static_cast<htps::s32>(a) - right.a);
        return *this;
    }

    constexpr Color& operator*=(Color const& right) noexcept
    {
        r = static_cast<value_type>((static_cast<htps::u32>(r) * right.r) /
                                    value_max);
        g = static_cast<value_type>((static_cast<htps::u32>(g) * right.g) /
                                    value_max);
        b = static_cast<value_type>((static_cast<htps::u32>(b) * right.b) /
                                    value_max);
        a = static_cast<value_type>((static_cast<htps::u32>(a) * right.a) /
                                    value_max);
        return *this;
    }

    constexpr Color& operator*=(htps::f32 const delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<htps::f32>(r) * delta);
        g = detail::ensureLimits<value_type>(static_cast<htps::f32>(g) * delta);
        b = detail::ensureLimits<value_type>(static_cast<htps::f32>(b) * delta);
        a = detail::ensureLimits<value_type>(static_cast<htps::f32>(a) * delta);
        return *this;
    }

    constexpr Color& operator/=(htps::f32 const delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<htps::f32>(r) / delta);
        g = detail::ensureLimits<value_type>(static_cast<htps::f32>(g) / delta);
        b = detail::ensureLimits<value_type>(static_cast<htps::f32>(b) / delta);
        a = detail::ensureLimits<value_type>(static_cast<htps::f32>(a) / delta);
        return *this;
    }

    constexpr value_type red() const noexcept { return r; }
    constexpr value_type green() const noexcept { return g; }
    constexpr value_type blue() const noexcept { return b; }
    constexpr value_type alpha() const noexcept { return a; }

private:
    value_type r;
    value_type g;
    value_type b;
    value_type a;
};

constexpr Color operator*(Color const& color, htps::f32 const delta) noexcept
{
    return Color{color} *= delta;
}

constexpr Color operator*(htps::f32 const delta, Color const& color) noexcept
{
    return Color{color} *= delta;
}

constexpr Color operator/(Color const& color, htps::f32 const delta) noexcept
{
    return Color{color} /= delta;
}

constexpr Color operator/(htps::f32 const delta, Color const& color) noexcept
{
    return Color{color} /= delta;
}

constexpr Color operator+(Color const& lhs, Color const& rhs) noexcept
{
    return (Color{lhs} += rhs);
}


inline scene::Color interpolate(scene::Color const& begin,
                                scene::Color const& end,
                                htps::f32 const delta)
{
    using namespace htps;
    f32 my_r{anim::interpolate(static_cast<f32>(begin.red()),
                               static_cast<f32>(end.red()), delta)};
    f32 my_g{anim::interpolate(static_cast<f32>(begin.green()),
                               static_cast<f32>(end.green()), delta)};
    f32 my_b{anim::interpolate(static_cast<f32>(begin.blue()),
                               static_cast<f32>(end.blue()), delta)};
    f32 my_a{anim::interpolate(static_cast<f32>(begin.alpha()),
                               static_cast<f32>(end.alpha()), delta)};

    return scene::Color{static_cast<u8>(my_r), static_cast<u8>(my_g),
                        static_cast<u8>(my_b), static_cast<u8>(my_a)};
}

namespace colors
{
static const Color Black{Color::value_min, Color::value_min, Color::value_min};
static const Color White{Color::value_max, Color::value_max, Color::value_max};
static const Color Red{Color::value_max, Color::value_min, Color::value_min};
static const Color Green{Color::value_min, Color::value_max, Color::value_min};
static const Color Blue{Color::value_min, Color::value_min, Color::value_max};
static const Color Yellow{Color::value_max, Color::value_max, Color::value_min};
static const Color Magenta{Color::value_max, Color::value_min,
                           Color::value_max};
static const Color Cyan{Color::value_min, Color::value_max, Color::value_max};
static const Color Transparent{Color::value_min, Color::value_min,
                               Color::value_min, Color::value_min};
}  // namespace colors

}  // namespace haf::scene

#endif
