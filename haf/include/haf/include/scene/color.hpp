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
    Color() noexcept;

    /**
     * @brief Construct a Color object from four values
     * @param red Red component of the color
     * @param green Green component of the color
     * @param blue Blue component of the color
     * @param alpha Alpha component of the color (Defaulted to opaque)
     */
    Color(value_type const red,
          value_type const green,
          value_type const blue,
          value_type const alpha = value_max) noexcept;

    Color(Color const&) noexcept = default;
    Color& operator=(Color const&) noexcept = default;
    Color(Color&&) noexcept                 = default;
    Color& operator=(Color&&) noexcept = default;

    /**
     * @brief Construct a Color object from another color, but with a
     * different alpha.
     * @param base_color The color that will give the r,g,b values
     * @param alpha The alpha value
     */
    Color(Color const& base_color, value_type const alpha) noexcept;

    explicit Color(htps::u32 const color) noexcept;

    static Color fromFloats(htps::f32 const red,
                            htps::f32 const green,
                            htps::f32 const blue,
                            htps::f32 const alpha = 1.0F) noexcept;

    Color& operator+=(Color const& right) noexcept
    {
        r = ensureLimits(r + right.r);
        g = ensureLimits(g + right.g);
        b = ensureLimits(b + right.b);
        a = ensureLimits(a + right.a);
        return *this;
    }

    Color& operator-=(Color const& right) noexcept
    {
        r = ensureLimits(static_cast<htps::s32>(r) - right.r);
        g = ensureLimits(static_cast<htps::s32>(g) - right.g);
        b = ensureLimits(static_cast<htps::s32>(b) - right.b);
        a = ensureLimits(static_cast<htps::s32>(a) - right.a);
        return *this;
    }

    Color& operator*=(Color const& right) noexcept;

    Color& operator*=(htps::f32 const delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<htps::f32>(r) * delta);
        g = detail::ensureLimits<value_type>(static_cast<htps::f32>(g) * delta);
        b = detail::ensureLimits<value_type>(static_cast<htps::f32>(b) * delta);
        a = detail::ensureLimits<value_type>(static_cast<htps::f32>(a) * delta);
        return *this;
    }

    Color& operator/=(htps::f32 const delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<htps::f32>(r) / delta);
        g = detail::ensureLimits<value_type>(static_cast<htps::f32>(g) / delta);
        b = detail::ensureLimits<value_type>(static_cast<htps::f32>(b) / delta);
        a = detail::ensureLimits<value_type>(static_cast<htps::f32>(a) / delta);
        return *this;
    }

    value_type red() const noexcept { return r; }
    value_type green() const noexcept { return g; }
    value_type blue() const noexcept { return b; }
    value_type alpha() const noexcept { return a; }

private:
    value_type r;
    value_type g;
    value_type b;
    value_type a;
};

/**
 * @brief Multiply two colors (They might be of different type). The result
 * is ensured to be a valid color of the source type
 *
 * @param rhs  Right hand side operand
 * @return Color with the resulting color
 */
Color operator*(Color const& lhs, Color const& rhs) noexcept;

/**
 * @brief Substract two colors (They might be of different type). The result
 * is ensured to be a valid color of the source type
 *
 * @param rhs  Right hand side operand
 * @return Color with the resulting color
 */
inline Color operator-(Color const& lhs, Color const& rhs) noexcept;

/**
 * @brief Equality comparation with another Color of the same type
 *
 * @param rhs Right part of the comparison
 * @return The colors are equal
 * @return The colors are not equal
 */
bool operator==(Color const& lhs, Color const& rhs) noexcept;

/**
 * @brief Unequality comparation with another Color of the same type
 *
 * @param rhs Right part of the comparison
 * @return The colors are not equal
 * @return The colors are equal
 */
bool operator!=(Color const& lhs, Color const& rhs) noexcept;

Color operator*(Color const& color, htps::f32 const delta) noexcept;

Color operator*(htps::f32 const delta, Color const& color) noexcept;

Color operator/(Color const& color, htps::f32 const delta) noexcept;

Color operator/(htps::f32 const delta, Color const& color) noexcept;

Color operator+(Color const& lhs, Color const& rhs) noexcept;

Color interpolate(Color const& begin, Color const& end, htps::f32 const delta);

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
